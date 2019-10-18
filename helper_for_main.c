#include "libftcorewar.h"

int ft_read_data_bytes(int fd)
{
    unsigned char bytes[4];
    int i;
    unsigned int val;

    i = 0;
    val = 0;
    read(fd, bytes, 4);
    while (i < 4)
    {
        val = val << 8;
        val= val + bytes[i];
        i++;
    }
    return (val);
}

void	read_data_players(t_carriage *frst, char *map, int cnt_plr)
{
	int			fd;
	t_carriage	*crn;
	int			nulls;
	char bytes[4];

	int a;
	crn = frst;
	while (crn)
	{
		fd = open(crn->file_name, O_RDONLY);
		if (fd == -1)
			exit(1);
        if (ft_read_data_bytes(fd) != COREWAR_EXEC_MAGIC)
            exit(1);
		if (read(fd, crn->header.prog_name, PROG_NAME_LENGTH) !=
			PROG_NAME_LENGTH)
			exit(1);
		if (read(fd, &nulls, 4) != 4)
			exit(1);
		crn->header.prog_size = ft_read_data_bytes(fd);
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

