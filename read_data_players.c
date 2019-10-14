#include "libftcorewar.h"

void read_data_players(t_carriage *frst, char *map, int cnt_plr)
{
    int fd;
    t_carriage *crn;
    int nulls;

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
		if (read(fd, crn->header.prog_name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
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
		if (read(fd, &map[crn->pc], crn->header.prog_size) != crn->header.prog_size)
			exit(1);
    	crn = crn->next;
	}
}