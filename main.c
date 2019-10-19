/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 20:23:30 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/16 20:34:58 by tbondare         ###   ########.fr       */
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

void	init_vm_data(t_vm_data *data)
{
	data->last_pl_said_alive = data->frst;
	data->loop_num = 0;
}

void free_mem(unsigned char *map, t_vm_data *data)
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

int		main(int argc, char **argv)
{
	unsigned char		*map;
	int			cnt_plr;
	t_vm_data	data;

	data.frst = NULL;
	data.is_dump = 0;
	data.dump_num = 0;
	cnt_plr = read_inp_str(argc, argv, &data);
	if (!data.frst)
	{
		ft_putstr("invalid input str");
		exit(1);
	}
	map = create_mem_map();
	read_data_players(data.frst, map, cnt_plr);
	sorting_list_carriage(&data.frst);
	init_vm_data(&data);
	ft_corewar(map, &data);
	free_mem(map, &data);
	return (0);
}
