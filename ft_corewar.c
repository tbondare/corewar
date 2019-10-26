/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_corewar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:54:48 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/26 18:17:28 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void	print_chemp_name(t_vm_data *data)
{
	ft_putstr("Contestant ");
	ft_putnbr(data->last_pl_said_alive->unic_num_plr);
	ft_putstr(", \"");
	ft_putstr(data->last_pl_said_alive->header.prog_name);
	ft_putstr("\", has won !\n");
}

void	if_loop_num_q_dump_num(unsigned char *map, t_vm_data *data)
{
	if (data->loop_num == data->dump_num)
	{
		ft_print_memory(map, MEM_SIZE);
		write(1, "\n", 1);
		exit(0);
	}
}

void print_cycle_num(int num, t_vm_data *data)
{
	if (data->is_v_flag)
	{
		ft_putstr("It is now cycle ");
		ft_putnbr(num);
		ft_putstr("\n");
	}
}

void	ft_corewar(unsigned char *map, t_vm_data *data)
{
	t_carriage	*crnt_carr;
	int			cnt;

	cnt = 0;
	crnt_carr = data->frst;
	print_cycle_num(1, data);
	while (1)
	{
		do_crnt_carr(crnt_carr, map, data);
		if (crnt_carr->is_killed == 0)
			cnt++;
		crnt_carr = crnt_carr->next;
		if (crnt_carr == NULL)
		{
			if (cnt <= 1)
			{
				print_chemp_name(data);
				break ;
			}
			crnt_carr = data->frst;
			data->loop_num++;
			print_cycle_num(data->loop_num + 1, data);
			if_loop_num_q_dump_num(map, data);
			cnt = 0;
		}
	}
}
