
#include "libftcorewar.h"

char *create_mem_map()
{
    char *map;

    map = (char*)malloc(sizeof(char) * MEM_SIZE);
    ft_bzero(map, MEM_SIZE);
    return (map);
}
