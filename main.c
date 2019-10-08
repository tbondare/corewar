#include "libftcorewar.h"

t_carriage *add_player_to_list(t_carriage **frst, char *argv)
{
    t_carriage *crn;

    if (*frst == NULL)
    {
        (*frst) = (t_carriage *)malloc(sizeof(t_carriage));
		(*frst)->unic_num = 0;
        (*frst)->file_name = argv;
		(*frst)->cnt_loop = 0;
        (*frst)->next = NULL;
		return (*frst);
    }
    else
    {
		crn = *frst;
		while (crn->next)
			crn = crn->next;
        crn->next = (t_carriage *)malloc(sizeof(t_carriage));
		crn->unic_num = 0;
        crn->next->file_name = argv;
		crn->cnt_loop = 0;
        crn->next->next = NULL;
		return (crn->next);
    }
}

int found_point_cor(char *file_name)
{
	char *point_str;

	point_str = ft_strchr(file_name, '.');
	if (point_str != NULL)
    {
        if (ft_strequ(point_str + 1, "cor") == 1)
            return (1);
    }
    return (0);
}

int found_same_unic_num (t_carriage **frst, int djt, int cnt_plr)
{
    t_carriage *crn;

    crn = *frst;
    while (crn)
    {
        if (crn->unic_num == djt)
        {
			crn->unic_num = cnt_plr;
			return (1);
        }
        crn = crn->next;
    }
    return (0);
}

int found_flg_min_n(char **argv, int *j, t_carriage **frst, int *cnt_plr)
{
	t_carriage *crn;

    if (ft_strequ(argv[*j], "-n") == 1)
    {
        *j++;
        if (ft_isdigit(argv[*j][0]) == 1 &&
        ft_atoi(argv[*j]) <= MAX_PLAYERS && ft_atoi(argv[*j]) >= 1)
        {
            if (found_point_cor(argv[++(*j)]) == 1)
            {
                (*cnt_plr)++;
                crn = add_player_to_list(frst, argv[*j]);
                found_same_unic_num(frst, ft_atoi(argv[(*j) - 1]), *cnt_plr);
                crn->unic_num = ft_atoi(argv[(*j) - 1]);
            }
            else
                return (0);
        }
        else
            return (0);
    }
    return (1);
}

int define_next_unic_num(t_carriage *frst)
{
	int num;
	t_carriage *crn;

	num = 1;
	while (num <= MAX_PLAYERS)
	{
		crn = frst;
		while (crn)
		{
			if (crn->unic_num == num)
				break;
			crn = crn->next;
		}
		if (crn == NULL)
			return (num);
		num++;
	}
	return (num);
}

int read_inp_str(int argc, char **argv, t_carriage **frst)
{
    int j;
    int cnt_plr;

    j = 1;
    cnt_plr = 0;
    while (j <= argc && cnt_plr <= MAX_PLAYERS)
    {
        if (found_flg_min_n(argv, &j, frst, &cnt_plr) != 1)
        {
            if (found_point_cor(argv[j]) == 1)
            {
                cnt_plr++;
                add_player_to_list(frst, argv[j]);
                (*frst)->unic_num = define_next_unic_num(*frst);
            }
        }
        j++;
    }
	return(cnt_plr);
}

void visual_map_carriages(t_carriage *frst, char *map)
{

}

void sorting_list_carriage(t_carriage *frst)
{
    t_carriage *crnt;
    t_carriage *a;
    t_carriage *b,
    t_carriage *c;
    t_carriage *d;
//    t_carriage *mem_prev;
//    t_carriage *mem_double_nxt;
//    t_carriage *mem_next;
//    t_carriage *mem_crnt;
    int i;

    i = 0;
    crnt = frst;
//    mem_prev = NULL;
//	mem_double_nxt = NULL;
//	mem_next = NULL;
	a = NULL;
	b = NULL;
	c = NULL;
	d = NULL;
    while (i <= MAX_PLAYERS)
    {
        crnt = frst;
        while(crnt)
        {
            if (crnt->next != NULL && crnt->unic_num < crnt->next->unic_num)
            {
                a = crnt->next->next;
                b = crnt->next;
                c = crnt;
                d =
//				mem_double_nxt = crnt->next->next;
//                crnt->next = mem_double_nxt;
//				mem_next = crnt->next;
//                if (mem_prev != NULL)
//                {
//                    mem_prev->next = crnt->next;
//                    crnt = mem_prev->next;
//                }
//				crnt->next->next = crnt;
//                if (mem_prev == NULL)
//                    frst = crnt->next;
            }
//            mem_prev = crnt;
            crnt = crnt->next;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    char *map;
    int cnt_plr;
    t_carriage *frst;

	frst = NULL;
    cnt_plr = read_inp_str(argc, argv, &frst);
    if(!frst)
        exit (1);
	map = create_mem_map();
    read_data_players(frst, map, cnt_plr);
    sorting_list_carriage(frst);
    visual_map_carriages(frst, map);
    ft_corewar(frst, map);
	return 0;
}