/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command_frome_byte_code.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 20:03:44 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/16 20:07:30 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void	read_command_argum(t_carriage *crnt_carr, char *map, int i_argum)
{
	int crnt_arg_size;

	crnt_arg_size = t2size[crnt_carr->command.argum_types[i_argum]];
	crnt_carr->command.argum[i_argum] =
		read_bytes(crnt_carr->next_pc, map, crnt_arg_size);
	crnt_carr->next_pc = (crnt_carr->next_pc + crnt_arg_size) % MEM_SIZE;
}

void	read_com_argums(t_op *info_com, t_carriage *crnt_carr, char *map)
{
	int i_argum;

	i_argum = 0;
	read_command_argum(crnt_carr, map, i_argum);
	while (i_argum < info_com->argum_nums)
	{
		crnt_carr->next_pc = (crnt_carr->next_pc + 1) % MEM_SIZE;
		read_command_argum(crnt_carr, map, i_argum);
		i_argum++;
	}
}

int		is_val_arg_tapes(t_op *info_com, t_carriage *crnt_carr)
{
	int i;

	i = 0;
	while (i < info_com->argum_nums)
	{
		if (!(crnt_carr->command.argum_types[i] && info_com->argum_types[i] ==
					crnt_carr->command.argum_types[i]))
			return (0);
		i++;
	}
	return (1);
}

void	read_arg_types(t_carriage *crnt_carr, char *map)
{
	char crnt_byte;

	crnt_carr->next_pc = (crnt_carr->next_pc + 1) % MEM_SIZE;
	crnt_byte = map[crnt_carr->next_pc];
	crnt_carr->command.argum_types[0] = code2t[crnt_byte >> 6];
	crnt_carr->command.argum_types[1] = code2t[(crnt_byte << 2) >> 6];
	crnt_carr->command.argum_types[2] = code2t[(crnt_byte << 4) >> 6];
}

int		read_command_frome_byte_code(t_carriage *crnt_carr, char *map)
{
	t_op *info_com;

	crnt_carr->command.oper_code = map[crnt_carr->pc];
	crnt_carr->next_pc = crnt_carr->pc;
	if (is_val_command_oper_code(crnt_carr->command.oper_code) != 1)
	{
		crnt_carr->next_pc = (crnt_carr->next_pc + 1) % MEM_SIZE;
		return (0);
	}
	info_com = &op_tab[crnt_carr->command.oper_code];
	crnt_carr->command.num_cycle = info_com->num_cycle - 1;
	if (is_argum_type(info_com, crnt_carr) != 0)
	{
		read_arg_types(crnt_carr, map);
		if (is_val_arg_tapes(info_com, crnt_carr) != 0)
			crnt_carr->next_pc = (crnt_carr->next_pc + 1) % MEM_SIZE;
		else
			return (0);
	}
	read_com_argums(info_com, crnt_carr, map);
	return (1);
}
