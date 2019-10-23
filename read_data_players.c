/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data_players.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:18:52 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/22 16:18:54 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void read_data_players2(t_carriage *crn, int *fd)
{
    int			nulls;

    if (read(*fd, crn->header.prog_name, PROG_NAME_LENGTH) !=
        PROG_NAME_LENGTH)
    {
        ft_putstr("invalid PROG_NAME_LENGTH ");
        ft_putstr(crn->file_name);
        exit(1);
    }
    if (read(*fd, &nulls, 4) != 4)
    {
        ft_putstr("invalid nulls after PROG_NAME_LENGTH ");
        ft_putstr(crn->file_name);
        exit(1);
    }
    crn->header.prog_size = ft_read_data_bytes(*fd);
    if (crn->header.prog_size > CHAMP_MAX_SIZE)
    {
        ft_putstr("invalid CHAMP_MAX_SIZE ");
        ft_putstr(crn->file_name);
        exit(1);
    }
}

void read_data_players3(t_carriage *crn, int *fd, unsigned char *map, int *cnt_plr)
{
    int			nulls;

    if (read(*fd, crn->header.comment, COMMENT_LENGTH) != COMMENT_LENGTH)
    {
        ft_putstr("invalid COMMENT_LENGTH ");
        ft_putstr(crn->file_name);
        exit(1);
    }
    if (read(*fd, &nulls, 4) != 4)
    {
        ft_putstr("invalid nulls_after_COMMENT_LENGTH ");
        ft_putstr(crn->file_name);
        exit(1);
    }
    crn->pc = MEM_SIZE / (*cnt_plr) * (crn->unic_num_plr - 1);
    if (read(*fd, &map[crn->pc], crn->header.prog_size) !=
        crn->header.prog_size)
    {
        ft_putstr("invalid header.prog_size ");
        ft_putstr(crn->file_name);
        exit(1);
    }
}

void	read_data_players(t_carriage *frst, unsigned char *map, int cnt_plr)
{
	int			fd;
	t_carriage	*crn;

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
        read_data_players2(crn, &fd);
        read_data_players3(crn, &fd, map, &cnt_plr);
		crn = crn->next;
	}
}
