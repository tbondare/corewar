#include "libftcorewar.h"

t_carriage *add_player_to_list(t_carriage **frst, char *argv)
{
    t_carriage *crn;

    if (*frst == NULL)
    {
        (*frst) = (t_carriage *)malloc(sizeof(t_carriage));
		ft_bzero((*frst)->reg, REG_NUMBER * sizeof(int));
		(*frst)->unic_num_plr = 0;
        (*frst)->file_name = argv;
		(*frst)->command.num_cycle = -1;
		(*frst)->cycles_to_die = CYCLE_TO_DIE;
		(*frst)->num_checks = 0;
		(*frst)->cnt_ccls_to_die = 0;
        (*frst)->command.is_arg_type = 1;
		(*frst)->num_oper_live = 0;
		(*frst)->num_cycle_end_alive = -1;
        (*frst)->next = NULL;
		return (*frst);
    }
    else
    {
		crn = *frst;
		while (crn->next)
			crn = crn->next;
        crn->next = (t_carriage *)malloc(sizeof(t_carriage));
		ft_bzero(crn->reg, REG_NUMBER * sizeof(int));
		crn->unic_num_plr = 0;
        crn->next->file_name = argv;
		crn->command.num_cycle = -1;
		crn->cycles_to_die = CYCLE_TO_DIE;
		crn->num_checks = 0;
		crn->cnt_ccls_to_die = 0;
		crn->command.is_arg_type = 1;
		crn->num_oper_live = 0;
		crn->num_cycle_end_alive = -1;
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
        if (crn->unic_num_plr == djt)
        {
			crn->unic_num_plr = cnt_plr;
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
                crn->unic_num_plr = ft_atoi(argv[(*j) - 1]);
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
			if (crn->unic_num_plr == num)
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
                (*frst)->unic_num_plr = define_next_unic_num(*frst);
            }
        }
        j++;
    }
	return(cnt_plr);
}

void visual_map_carriages(t_carriage *frst, char *map)
{

}

void sorting_list_carriage(t_carriage **frst)
{
    t_carriage *crnt;
    t_carriage *mem[4];
    int i;

    i = 0;
	mem[0] = NULL;
    while (i <= MAX_PLAYERS)
    {
        crnt = *frst;
        while(crnt)
        {
            if (crnt->next != NULL && crnt->unic_num_plr < crnt->next->unic_num_plr)
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

void init_vm_data(t_vm_data *data)
{
	data->last_pl_said_alive = data->frst;
	data->loop_num = 0;
}

int main(int argc, char **argv)
{
    char *map;
    int cnt_plr;
    t_vm_data data;

	data.frst = NULL;
    cnt_plr = read_inp_str(argc, argv, &data.frst);
    if(!data.frst)
        exit (1);
	map = create_mem_map();
    read_data_players(data.frst, map, cnt_plr);
    sorting_list_carriage(&data.frst);
    visual_map_carriages(data.frst, map);
    init_vm_data(&data);
    ft_corewar(map, &data);
	return 0;
}