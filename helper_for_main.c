#include "libftcorewar.h"

int ft_bytes_to_int(unsigned char *bytes, int num_bytes)
{
	unsigned int val;
	int i;

	i = 0;
	val = 0;
	while (i < num_bytes)
	{
		val = val << 8;
		val= val + bytes[i];
		i++;
	}
	return (val);
}

int ft_read_data_bytes(int fd)
{
    unsigned char bytes[4];

    read(fd, bytes, 4);
	return (ft_bytes_to_int(bytes, 4));
}

void	read_data_players(t_carriage *frst, unsigned char *map, int cnt_plr)
{
	int			fd;
	t_carriage	*crn;
	int			nulls;
	unsigned char bytes[4];

	int a;
	crn = frst;
	while (crn)
	{
		fd = open(crn->file_name, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr("invalid fd");
			exit(1);
		}
        if (ft_read_data_bytes(fd) != COREWAR_EXEC_MAGIC)
		{
			ft_putstr("invalid COREWAR_EXEC_MAGIC of player ");
			ft_putstr(crn->file_name);
        	exit(1);
		}
		if (read(fd, crn->header.prog_name, PROG_NAME_LENGTH) !=
			PROG_NAME_LENGTH)
		{
			ft_putstr("invalid PROG_NAME_LENGTH ");
			ft_putstr(crn->file_name);
			exit(1);
		}
		if (read(fd, &nulls, 4) != 4)
		{
			ft_putstr("invalid nulls after PROG_NAME_LENGTH ");
			ft_putstr(crn->file_name);
			exit(1);
		}
		crn->header.prog_size = ft_read_data_bytes(fd);
        if (crn->header.prog_size > CHAMP_MAX_SIZE)
		{
        	ft_putstr("invalid CHAMP_MAX_SIZE ");
			ft_putstr(crn->file_name);
        	exit(1);
		}
        if (read(fd, crn->header.comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		{
			ft_putstr("invalid COMMENT_LENGTH ");
			ft_putstr(crn->file_name);
        	exit(1);
		}
        if (read(fd, &nulls, 4) != 4)
		{
			ft_putstr("invalid nulls_after_COMMENT_LENGTH ");
			ft_putstr(crn->file_name);
			exit(1);
		}
		crn->pc = MEM_SIZE / cnt_plr * (crn->unic_num_plr - 1);
		if (read(fd, &map[crn->pc], crn->header.prog_size) !=
			crn->header.prog_size)
		{
			ft_putstr("invalid header.prog_size ");
			ft_putstr(crn->file_name);
			exit(1);
		}
		crn = crn->next;
	}
}

void	sorting_list_carriage(t_carriage **frst)
{
	t_carriage	*crnt;
	t_carriage	*mem[4];
	int			i;

	i = 0;
	ft_bzero(mem, 4);
	while (i <= MAX_PLAYERS)
	{
		crnt = *frst;
		mem[0] = NULL;
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

void ft_print_memory(const void *add, size_t size)
{
	const unsigned char *var;
	int i;
	char c;
	unsigned char prev;
	int j;
	int mem_j;

	var = (const unsigned char*)add;
	i = 0;
	j = 0;
	while (size--)
	{
		prev = var[i];
		prev = prev / 16;
		if (prev % 16 > 9)
			c = prev % 16 - 10 + 'a';
		else
			c = prev % 16 + '0';
		write(1, &c, 1);
		prev = var[i];
		if (prev % 16 > 9)
			c = prev % 16 - 10 + 'a';
		else
			c = prev % 16 + '0';
		write(1, &c, 1);
		i++;
		if ((i + 1) % 2)
			write(1, " ", 1);
		if (!(i % 16))
			write(1, "\n", 1);
	}
	if (i % 16)
	{
		mem_j = i - j;
		while (i % 16)
		{
			write(1, "  ", 2);
			if ((i + 1) % 2)
				write(1, " ", 1);
			i++;
		}
		while (mem_j--)
		{
			c = var[j++];
			write(1, &c, 1);
		}
		write(1, "\n", 1);
	}
}