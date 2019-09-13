//
// Created by Tetiana BONDARENKO on 2019-09-13.
//

#include "libftcorewar.h"

void ft_corewar(t_carriage *frst, char **map)
{
    int i;
    int cnt_rounds;
    int num_live_performed;
    t_carriage *said_alive;
    int num_checks;

    i = 0;
    cnt_rounds = 0;
    said_alive = frst;
    num_live_performed = CYCLE_TO_DIE;
    while (said_alive)
        said_alive = said_alive->next;
    while (i >= 0)
    {

    }
}
