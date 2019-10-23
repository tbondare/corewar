/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_commands3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:48:07 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/16 19:50:26 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void	ft_oper_or(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
	crnt_carr->reg[crnt_carr->command.argum[2]] =
		get_arg_value(crnt_carr, 0, map) | get_arg_value(crnt_carr, 1, map);
	change_carry(crnt_carr, 2);
}

void	ft_oper_xor(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
	crnt_carr->reg[crnt_carr->command.argum[2]] =
		get_arg_value(crnt_carr, 0, map) ^ get_arg_value(crnt_carr, 1, map);
	change_carry(crnt_carr, 2);
}

void	ft_oper_zjmp(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
	if (crnt_carr->carry == 1)
	{
		crnt_carr->next_pc = (crnt_carr->pc + crnt_carr->command.argum[0] % IDX_MOD) % MEM_SIZE;
		if (crnt_carr->next_pc < 0)
			crnt_carr->next_pc = MEM_SIZE + crnt_carr->next_pc;
	}
}

void	ft_oper_ldi(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
	crnt_carr->reg[crnt_carr->command.argum[2]] =
		read_bytes(crnt_carr->pc + (get_arg_value(crnt_carr, 0, map) +
					get_arg_value(crnt_carr, 1, map)) % IDX_MOD, map, 4);
}

void	ft_oper_sti(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
	write_bytes_from_int(crnt_carr->pc +
	(get_arg_value(crnt_carr, 1, map) +
	get_arg_value(crnt_carr, 2, map)) % IDX_MOD, map,
			(unsigned int)crnt_carr->reg[crnt_carr->command.argum[0]]);
}
