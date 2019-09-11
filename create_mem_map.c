//
// Created by Tetiana BONDARENKO on 2019-09-11.
//
#include "libftcorewar.h"

char **create_mem_map(int max)
{
    char **map;

    map = (char**)malloc(sizeof(char) * max);
    ft_bzero(*map, max);
    return (map);
}

void init_map(char **map, t_list_players *frst);
{

}