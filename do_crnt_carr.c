/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_for_corewar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:10:23 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/22 16:10:28 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void print_command(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
	int c;

    (void)data;
	ft_putstr("P    ");
	ft_putnbr(crnt_carr->unic_num_carr);
	ft_putstr(" | ");
	ft_putstr(tab_op[crnt_carr->command.oper_code].name);
	ft_putstr(" ");
	c = 0;
	while (c < tab_op[crnt_carr->command.oper_code].argum_nums)
	{
		if (crnt_carr->command.argum_types[c] == T_REG)
		{
			ft_putstr("r");
			ft_putnbr(crnt_carr->command.argum[c] + 1);
		}
		else
			ft_putnbr(crnt_carr->command.argum[c]);
		c++;
		if (c < tab_op[crnt_carr->command.oper_code].argum_nums)
			ft_putstr(" ");
	}
	ft_putstr("\n");
	ft_putstr("ADV ");
	ft_putnbr(crnt_carr->next_pc - crnt_carr->pc);
	ft_putstr(" (");
	print_address(crnt_carr->pc, "");
	ft_putstr(" -> ");
	print_address(crnt_carr->next_pc, "");
	ft_putstr(") ");
	if (crnt_carr->next_pc > crnt_carr->pc)
		ft_print_bytes(&map[crnt_carr->pc], crnt_carr->next_pc - crnt_carr->pc);
	ft_putstr("\n");
}

void	do_command(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
	if (data->is_v_flag)
		print_command(crnt_carr, map, data);
	tab_op[crnt_carr->command.oper_code].fun(crnt_carr, map, data);
	crnt_carr->pc = crnt_carr->next_pc;
}

void	check_alive(t_carriage *crnt_carr, t_vm_data *data)
{
//	if (crnt_carr->num_oper_live >= NBR_LIVE)
//	{
//		crnt_carr->cycles_to_die = crnt_carr->cycles_to_die - CYCLE_DELTA;
//		crnt_carr->num_checks = 0;
//	}
//	else
//	{
//		crnt_carr->num_checks++;
//		if (crnt_carr->num_checks == MAX_CHECKS)
//			crnt_carr->cycles_to_die = crnt_carr->cycles_to_die - CYCLE_DELTA;
//	}
//	if (crnt_carr->num_oper_live == 0 || crnt_carr->cycles_to_die <= 0)
//	{
//		crnt_carr->is_killed = 1;
//		if (data->is_v_flag)
//		{
//			ft_putnbr(crnt_carr->unic_num_carr);
//			ft_putstr("   KILLED\n");
//		}
//	}
}

void	do_check(t_carriage *crnt_carr, t_vm_data *data)
{
	if ((data->cnt_ccls_to_die >= data->cycles_to_die &&
		data->loop_num - crnt_carr->last_op_live_cycle >= data->cycles_to_die) ||
			data->cycles_to_die <= 0)
	{
		crnt_carr->is_killed = 1;
		if (data->is_v_flag)
		{
			ft_putnbr(crnt_carr->unic_num_carr);
			ft_putstr("   KILLED\n");
		}
	}
//	crnt_carr->cnt_ccls_to_die++;
//	if (crnt_carr->cnt_ccls_to_die > 0)
//	{
//		if (crnt_carr->cnt_ccls_to_die == CYCLE_TO_DIE)
//		{
//			crnt_carr->cnt_ccls_to_die = 0;
//			check_alive(crnt_carr, data);
//			crnt_carr->num_oper_live = 0;
//		}
//	}
//	else
//		check_alive(crnt_carr, data);
}

void	do_crnt_carr(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data)
{
	if (crnt_carr->is_killed == 1)
		return ;
	if (crnt_carr->command.num_cycle == -1)
	{
		if (read_command_frome_byte_code(crnt_carr, map) == 0)
			crnt_carr->command.num_cycle = -1;
		else
		{
			if (crnt_carr->command.num_cycle > 0)
				crnt_carr->command.num_cycle--;
		}
		if (crnt_carr->command.num_cycle == 0)
			do_command(crnt_carr, map, data);
	}
	else
	{
		if (crnt_carr->command.num_cycle > 0)
			crnt_carr->command.num_cycle--;
		else
		{
			do_command(crnt_carr, map, data);
			crnt_carr->command.num_cycle = -1;
		}
	}
	do_check(crnt_carr, data);
}
