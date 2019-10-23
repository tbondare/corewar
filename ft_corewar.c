/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_corewar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:54:48 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/22 16:10:32 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void	print_chemp_name(t_vm_data *data)
{
	ft_putstr("Contestant ");
	ft_putnbr(data->last_pl_said_alive->unic_num_plr);
	ft_putstr(", \"");
	ft_putstr(data->last_pl_said_alive->header.prog_name);
	ft_putstr("\", has won !");
}

void if_loop_num_q_dump_num(unsigned char *map, t_vm_data *data)
{
    if (data->loop_num == data->dump_num)
    {
        ft_print_memory(map, MEM_SIZE);
        exit(0);
    }
}

void	ft_corewar(unsigned char *map, t_vm_data *data)
{
	t_carriage	*crnt_carr;
	int			cnt;

	cnt = 0;
	crnt_carr = data->frst;
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
            if_loop_num_q_dump_num(map, data);
			cnt = 0;
		}
	}
}
