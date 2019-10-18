/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_commands2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:44:40 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/16 19:47:37 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void	ft_oper_st(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
	if (crnt_carr->command.argum_types[1] == T_REG)
		crnt_carr->reg[crnt_carr->command.argum[0]] =
			crnt_carr->reg[crnt_carr->command.argum[1]];
	else if (crnt_carr->command.argum_types[1] == T_IND)
	{
		write_bytes(crnt_carr->command.argum[1] % IDX_MOD + crnt_carr->pc,
				crnt_carr->command.argum[0], map);
	}
}

void	ft_oper_add(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
	crnt_carr->reg[crnt_carr->command.argum[2]] =
		crnt_carr->reg[crnt_carr->command.argum[0]] +
		crnt_carr->reg[crnt_carr->command.argum[1]];
	change_carry(crnt_carr, 2);
}

void	ft_oper_sub(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
	crnt_carr->reg[crnt_carr->command.argum[2]] =
		crnt_carr->reg[crnt_carr->command.argum[0]] -
		crnt_carr->reg[crnt_carr->command.argum[1]];
	change_carry(crnt_carr, 2);
}

void	ft_oper_and(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
	crnt_carr->reg[crnt_carr->command.argum[2]] =
		get_arg_value(crnt_carr, 0, map) & get_arg_value(crnt_carr, 1, map);
	change_carry(crnt_carr, 2);
}
