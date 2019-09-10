#include "libftcorewar.h"

void add_player_to_list(t_players **frst)
{
    t_players *crn;

    crn = NULL;
    if (*frst == NULL)
    {
        *frst = (t_players *) malloc(sizeof(t_players));
        (*frst)->next = NULL;
    }
    else
    {
        *frst = (t_players *) malloc(sizeof(t_players));
        crn = *frst;
    }
}

int found_point_cor(char *argv)
{
    t_players *frst;

    frst = NULL;
    if (ft_strchr(argv, '.') != NULL)
    {
        if (ft_strequ(argv, "cor") == 1)
            add_player_to_list(&frst);
        return (1);
    }
    else
        return (0);
}

int found_same_unic_num (t_players **frst, int djt)
{

}

int found_flg_min_n(char **argv, int *j, t_players **frst)
{
    if (ft_strequ(argv[*j], "-n") == 1)
    {
        *j++;
        if (ft_isdigit(argv[*j][0]) == 1
            && ft_atoi(argv[*j][0]) <= MAX_PLAYERS && ft_atoi(argv[*j][0]) >= 1)
        {
            if (found_point_cor(argv[++(*j)]) == 1)
            {
                (*frst)->cnt_plrs++;
                add_player_to_list(&frst);
                if (found_same_unic_num(&frst, ft_atoi(argv[--(*j)]) == 0))
                    (*frst)->unic_num = ft_atoi(argv[--(*j)]);
                read_data_players(argv[++(*j)]);
            }
            else
                return (0);
        }
        else
            return (0);
    }
    return (1);
}

void read_inp_str(int argc, char **argv)
{
    int j;
    t_players *frst;

    j = 1;
    while (j <= argc)
    {
        if (frst->cnt_plrs > 4)
            return ;
        if (found_flg_min_n(argv, &j, &frst) == 1)
        {
            j++;
            continue ;
        }
        else
        {
            if (found_point_cor(argv[j]) == 1)
            {
                frst->cnt_plrs++;
                add_player_to_list(&frst);
                frst->unic_num = ft_atoi(argv[--(j)]);
                read_data_players(argv[++(j)]);
            }
        }
        j++;
    }
}

int main(int argc, char **argv)
{
    read_inp_str(argc, argv);

	return 0;
}