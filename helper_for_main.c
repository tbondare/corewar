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

void write_introduction(t_carriage *frst)
{
	t_carriage *crn;

	crn = frst;
	ft_putstr("Introduction contestants...\n");
	while (crn)
	{
		ft_putstr("* Player ");
		ft_putnbr(crn->unic_num_plr);
		ft_putstr(", weighting ");
		ft_putnbr(crn->header.prog_size);
		ft_putstr(" bytes, \"");
		ft_putstr(crn->header.prog_name);
		ft_putstr("\" (\"");
		ft_putstr(crn->header.comment);
		ft_putstr("\") ! \n");
		crn = crn->next;
	}
}

void	read_data_players(t_carriage *frst, unsigned char *map, int cnt_plr)
{
	int			fd;
	t_carriage	*crn;
	int			nulls;
	unsigned char bytes[4];

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

void print_address(int i)
{
	char str[4];
	int j;

	j = 3;
	ft_memset(str, '0', 4);
	write(1, "0", 1);
	write(1, "x", 1);
	while (j >= 0 && i)
	{
		if (i % 16 > 9)
			str[j] = i % 16 + 'a' - 10;
		else
			str[j] = i % 16 + '0';
		i = i / 16;
		j--;
	}
	write(1, str, 4);
	write(1, " : ", 3);
}

void ft_print_memory(const unsigned char *var, size_t size)
{
	int i;
	char c;
	unsigned char prev;

	i = 0;
	print_address(i);
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
		write(1, " ", 1);
		if (!(i % 64) && size != 0)
		{
			write(1, "\n", 1);
			print_address(i);
		}
	}
}