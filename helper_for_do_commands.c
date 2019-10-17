/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_for_do_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 20:00:23 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/16 20:03:14 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

int		get_arg_value(t_carriage *crnt_carr, int index_arg, char *map)
{
	if (crnt_carr->command.argum_types[index_arg] == T_REG)
		return (crnt_carr->reg[crnt_carr->command.argum[index_arg]]);
	if (crnt_carr->command.argum_types[index_arg] == T_DIR)
		return (crnt_carr->command.argum[index_arg]);
	if (crnt_carr->command.argum_types[index_arg] == T_IND)
		return (read_bytes(crnt_carr->command.argum[index_arg] %
					IDX_MOD + crnt_carr->pc, map, 4));
}

int		read_bytes(int start_address, char *map, int num_bytes)
{
	char	bytes[4];
	int		i;

	i = 0;
	ft_bzero(bytes, 4);
	while (i < num_bytes)
	{
		bytes[i] = map[start_address];
		start_address = (start_address + 1) % MEM_SIZE;
		i++;
	}
	i = 0;
	ft_memcpy(&i, &bytes[0], num_bytes);
	i = i >> ((sizeof(int) - num_bytes) * 8);
	return (i);
}

void	write_bytes(int start_address, int value, char *map)
{
	int i;

	i = 0;
	while (i < 4)
	{
		map[start_address] = ((char*)(&value))[i];
		start_address = (start_address + 1) % MEM_SIZE;
		i++;
	}
}

void	change_carry(t_carriage *crnt_carr, int ind)
{
	if (crnt_carr->reg[crnt_carr->command.argum[ind]] == 0)
		crnt_carr->carry = 1;
	else
		crnt_carr->carry = 0;
}