/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_commands4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:50:50 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/19 20:04:23 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void	copy_carr(t_carriage *crnt_carr, t_vm_data *data, int new_pc)
{
	t_carriage *new_carr;

	new_carr = (t_carriage *)malloc(sizeof(t_carriage));
	ft_memcpy(new_carr->reg, crnt_carr->reg, sizeof(int) * REG_NUMBER);
	new_carr->unic_num_plr = crnt_carr->unic_num_plr;
	new_carr->file_name = crnt_carr->file_name;
	new_carr->command.num_cycle = crnt_carr->command.num_cycle;
	new_carr->cycles_to_die = crnt_carr->cycles_to_die;
	new_carr->num_checks = crnt_carr->num_checks;
	new_carr->cnt_ccls_to_die = crnt_carr->cnt_ccls_to_die;
	new_carr->command.is_arg_type = crnt_carr->command.is_arg_type;
	new_carr->num_oper_live = crnt_carr->num_oper_live;
	new_carr->num_cycle_end_alive = crnt_carr->num_cycle_end_alive;
	new_carr->carry = crnt_carr->carry;
	new_carr->next = data->frst;
	data->frst = new_carr;
	new_pc = new_pc % MEM_SIZE;
	if (new_pc < 0)
		new_pc = MEM_SIZE + new_pc;
	new_carr->pc = new_pc;
	new_carr->next_pc = new_pc;
}

void	ft_oper_fork(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
	copy_carr(crnt_carr, data, crnt_carr->pc +
			crnt_carr->command.argum[0] % IDX_MOD);
}

void	ft_oper_lld(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
	int address;

	if (crnt_carr->command.argum_types[0] == T_DIR)
		crnt_carr->reg[crnt_carr->command.argum[1]] =
			crnt_carr->command.argum[0];
	else if (crnt_carr->command.argum_types[0] == T_IND)
	{
		address = crnt_carr->command.argum[0] + crnt_carr->pc;
		crnt_carr->reg[crnt_carr->command.argum[1]] =
			read_bytes(address, map, sizeof(int));
	}
	change_carry(crnt_carr, 1);
}

void	ft_oper_lldi(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
	crnt_carr->reg[crnt_carr->command.argum[2]] =
		read_bytes(crnt_carr->pc + (get_arg_value(crnt_carr, 0, map) +
					get_arg_value(crnt_carr, 1, map)), map, 4);
}

void	ft_oper_lfork(t_carriage *crnt_carr, unsigned char *map,
		t_vm_data *data)
{
	copy_carr(crnt_carr, data, crnt_carr->pc + crnt_carr->command.argum[0]);
}
