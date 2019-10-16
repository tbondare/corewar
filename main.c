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

char	*create_mem_map(void)
{
	char *map;

	map = (char*)malloc(sizeof(char) * MEM_SIZE);
	ft_bzero(map, MEM_SIZE);
	return (map);
}

void	read_data_players(t_carriage *frst, char *map, int cnt_plr)
{
	int			fd;
	t_carriage	*crn;
	int			nulls;

	crn = frst;
	while (crn)
	{
		fd = open(crn->file_name, O_RDONLY);
		if (fd == -1)
			exit(1);
		if (read(fd, &(crn->header.magic), 4) != 4)
			exit(1);
		if (crn->header.magic != COREWAR_EXEC_MAGIC)
			exit(1);
		if (read(fd, crn->header.prog_name, PROG_NAME_LENGTH) !=
				PROG_NAME_LENGTH)
			exit(1);
		if (read(fd, &nulls, 4) != 4)
			exit(1);
		if (read(fd, &(crn->header.prog_size), 4) != 4)
			exit(1);
		if (crn->header.prog_size > CHAMP_MAX_SIZE)
			exit(1);
		if (read(fd, crn->header.comment, COMMENT_LENGTH) != COMMENT_LENGTH)
			exit(1);
		if (read(fd, &nulls, 4) != 4)
			exit(1);
		crn->pc = MEM_SIZE / cnt_plr * (crn->unic_num_plr - 1);
		if (read(fd, &map[crn->pc], crn->header.prog_size) !=
				crn->header.prog_size)
			exit(1);
		crn = crn->next;
	}
}

void	sorting_list_carriage(t_carriage **frst)
{
	t_carriage	*crnt;
	t_carriage	*mem[4];
	int			i;

	i = 0;
	mem[0] = NULL;
	while (i <= MAX_PLAYERS)
	{
		crnt = *frst;
		while (crnt)
		{
			if (crnt->next != NULL &&
					crnt->unic_num_plr < crnt->next->unic_num_plr)
			{
				mem[1] = crnt;
				mem[2] = crnt->next;
				mem[3] = crnt->next->next;
				mem[2]->next = mem[1];
				mem[1]->next = mem[3];
				if (mem[0] != NULL)
					mem[0]->next = mem[2];
				else
					*frst = mem[2];
				crnt = mem[2];
			}
			mem[0] = crnt;
			crnt = crnt->next;
		}
		i++;
	}
}

void	init_vm_data(t_vm_data *data)
{
	data->last_pl_said_alive = data->frst;
	data->loop_num = 0;
}

int		main(int argc, char **argv)
{
	char		*map;
	int			cnt_plr;
	t_vm_data	data;

	data.frst = NULL;
	cnt_plr = read_inp_str(argc, argv, &data.frst);
	if (!data.frst)
		exit(1);
	map = create_mem_map();
	read_data_players(data.frst, map, cnt_plr);
	sorting_list_carriage(&data.frst);
	init_vm_data(&data);
	ft_corewar(map, &data);
	return (0);
}
