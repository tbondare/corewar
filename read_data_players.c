#include "libftcorewar.h"

void read_data_players(t_list_players **frst)
{
    int fd;

    if (fd = open((*frst)->name, O_RDONLY) == -1)
        exit(0);


}