/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 20:23:30 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/25 22:15:14 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

unsigned char	*create_mem_map(void)
{
	unsigned char *map;

	map = (unsigned char*)malloc(sizeof(unsigned char) * MEM_SIZE);
	ft_bzero(map, MEM_SIZE);
	return (map);
}

void			init_vm_data(t_vm_data *data)
{
	data->last_pl_said_alive = data->frst;
	data->loop_num = 0;
}

void			free_mem(unsigned char *map, t_vm_data *data)
{
	t_carriage *next;

	free(map);
	while (data->frst)
	{
		next = data->frst->next;
		free(data->frst);
		data->frst = next;
	}
}

int				main(int argc, char **argv)
{
	unsigned char	*map;
	int				cnt_plr;
	t_vm_data		data;

	data.frst = NULL;
	data.cycles_to_die = CYCLE_TO_DIE;
	data.num_oper_live = 0;
	data.num_checks_without_cycles_to_die_change = 0;
	data.dump_num = -1;
	data.cnt_ccls_to_die = 0;
	cnt_plr = read_inp_str(argc, argv, &data);
	data.carg_num = cnt_plr;

	if (!data.frst)
	{
		ft_putstr("invalid input str\n");
		exit(1);
	}
	map = create_mem_map();
	read_data_players(data.frst, map, cnt_plr);
//	write_introduction(data.frst);
	sorting_list_carriage(&data.frst);
    write_introduction(data.frst);
	init_vm_data(&data);
	ft_corewar(map, &data);
	free_mem(map, &data);
	return (0);
}
