/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_for_do_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 20:00:23 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/19 20:17:50 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

int		get_arg_value(t_carriage *crnt_carr, int index_arg, unsigned char *map)
{
	if (crnt_carr->command.argum_types[index_arg] == T_REG)
		return (crnt_carr->reg[crnt_carr->command.argum[index_arg]]);
	if (crnt_carr->command.argum_types[index_arg] == T_DIR)
		return (crnt_carr->command.argum[index_arg]);
	if (crnt_carr->command.argum_types[index_arg] == T_IND)
		return (read_bytes(crnt_carr->command.argum[index_arg] %
					IDX_MOD + crnt_carr->pc, map, 4));
    else
        return (0);
}

int		read_bytes(int start_address, unsigned char *map, int num_bytes)
{
	unsigned char	bytes[4];
	int				i;

	start_address = start_address % MEM_SIZE;
	if (start_address < 0)
		start_address = MEM_SIZE + start_address;
	i = 0;
	ft_bzero(bytes, 4);
	while (i < num_bytes)
	{
		bytes[i] = map[start_address];
		start_address = (start_address + 1) % MEM_SIZE;
		i++;
	}
	return (ft_bytes_to_int(bytes, num_bytes));
}

void	write_bytes_from_int(int start_address, unsigned char *map, unsigned int val)
{
	int j;

	start_address = start_address % MEM_SIZE;
	if (start_address < 0)
		start_address = MEM_SIZE + start_address;
	j = 3;
	while (j >= 0)
	{
		map[(start_address + j) % MEM_SIZE] = (unsigned char)(val & 255);
		val = val >> 8;
		j--;
	}
}

void	change_carry(t_carriage *crnt_carr, int ind)
{
	if (crnt_carr->reg[crnt_carr->command.argum[ind]] == 0)
		crnt_carr->carry = 1;
	else
		crnt_carr->carry = 0;
}
