/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_commands1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:41:32 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/16 19:44:14 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void	ft_oper_live(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
    (void)data;
    (void)map;
    data->num_oper_live++;
	crnt_carr->last_op_live_cycle = data->loop_num;
	if (crnt_carr->command.argum[0] == -crnt_carr->unic_num_plr)
	{
		data->last_pl_said_alive = crnt_carr;
		ft_putstr("A process shows that player ");
		ft_putnbr(crnt_carr->unic_num_plr);
		ft_putstr(" (");
		ft_putstr(crnt_carr->header.prog_name);
		ft_putstr(") is alive\n");
	}
}

void	ft_oper_ld(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
	int address;

    (void)data;
	if (crnt_carr->command.argum_types[0] == T_DIR)
		crnt_carr->reg[crnt_carr->command.argum[1]] =
			crnt_carr->command.argum[0];
	else if (crnt_carr->command.argum_types[0] == T_IND)
	{
		address = crnt_carr->command.argum[0] % IDX_MOD + crnt_carr->pc;
		crnt_carr->reg[crnt_carr->command.argum[1]] =
			read_bytes(address, map, sizeof(int));
	}
	change_carry(crnt_carr, 1);
}

void	ft_oper_aff(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
    (void)map;
    (void)data;
	write(1, &crnt_carr->reg[crnt_carr->command.argum[0]], 1);
}
