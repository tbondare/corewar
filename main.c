#include "libftcorewar.h"

void add_player_to_list(t_list_players **frst, char *argv)
{
    t_list_players *new;

    if (*frst == NULL)
    {
        (*frst) = (t_list_players *)malloc(sizeof(t_list_players));
        (*frst)->name = (char *)malloc(sizeof(char) * ft_strlen(argv));
        (*frst)->name = argv;
        (*frst)->next = NULL;
    }
    else
    {
        new = (t_list_players *)malloc(sizeof(t_list_players));
        new->name = (char *)malloc(sizeof(char) * ft_strlen(argv));
        new->name = argv;
        (*frst)->next = new;
    }
}

int found_point_cor(char *argv)
{
    if (ft_strchr(argv, '.') != NULL)
    {
        if (ft_strequ(argv, "cor") == 1)
            return (1);
    }
    return (0);
}

int found_same_unic_num (t_list_players **frst, int djt)
{
    t_list_players *crn;

    crn = *frst;
    while (crn)
    {
        if (crn->unic_num == djt)
        {

        }
        crn = crn->next;

    }
    return (0);
}

int found_flg_min_n(char **argv, int *j, t_list_players **frst)
{
    if (ft_strequ(argv[*j], "-n") == 1)
    {
        *j++;
        if (ft_isdigit(argv[*j][0]) == 1 &&
        ft_atoi(argv[*j][0]) <= MAX_PLAYERS && ft_atoi(argv[*j][0]) >= 1)
        {
            if (found_point_cor(argv[++(*j)]) == 1)
            {
                (*frst)->max_plrs++;
                add_player_to_list(frst, argv[*j]);
                if (found_same_unic_num(frst, ft_atoi(argv[--(*j)]) == 0))
                    (*frst)->unic_num = *j;
            }
            else
                return (0);
        }
        else
            return (0);
    }
    return (1);
}

int read_inp_str(int argc, char **argv, t_list_players **frst)
{
    int j;

    j = 1;
    (*frst)->max_plrs = 0;
    while (j <= argc || (*frst)->max_plrs <= 4)
    {
        if (found_flg_min_n(argv, &j, frst) == 1)
        {
            j++;
            continue ;
        }
        else
        {
            if (found_point_cor(argv[j]) == 1)
            {
                (*frst)->max_plrs++;
                add_player_to_list(frst, argv[j]);
                (*frst)->unic_num = ft_atoi(argv[--(j)]);
            }
        }
        j++;
    }
}

int main(int argc, char **argv)
{
    int **map;
    t_list_players *frst;

    map = create_mem_map(MEM_SIZE);
    frst = read_inp_str(argc, argv, &frst);
    if(!frst)
    {
        free(map);
        exit (0);
    }
    read_data_players(&frst);
    init_map(map, frst);
	return 0;
}