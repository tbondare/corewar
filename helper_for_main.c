#include "libftcorewar.h"

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

