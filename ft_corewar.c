
#include "libftcorewar.h"

//    int i;
//    int cnt_rounds;
//    int num_live_performed;
//    t_carriage *said_alive;
//    int num_checks;
//
//    i = 0;
//    cnt_rounds = 0;
//    said_alive = frst;
//    num_live_performed = CYCLE_TO_DIE;
//    while (said_alive)
//        said_alive = said_alive->next;
//    while (i >= 0)
//    {
//
//    }

int is_val_command_oper_code(int crnt_oper_code)
{
    if (crnt_oper_code > 0 && crnt_oper_code < 17)
        return (1);
    else
        return (0);
}

int is_argum_type(t_op *info_com, int i_argum)
{

}

void read_command_argum(t_carriage *crnt_carr, char *map, int i_pc, int i_argum)
{

}

int read_command_frome_byte_code(t_carriage *crnt_carr, char *map)
{
	t_op *info_com;
	int i_argum;
	int i_pc;

	i_argum = 0;
	crnt_carr->command.oper_code = map[crnt_carr->pc];
	if (is_val_command_oper_code(crnt_carr->command.oper_code) != 1)
	{
		crnt_carr->pc = (crnt_carr->pc + 1) % MEM_SIZE;
		return (0);
	}
	info_com = &op_tab[crnt_carr->command.oper_code];
	i_pc = crnt_carr->pc;
	while (i_argum < info_com->argum_nums)
	{
		if (is_argum_type(info_com, i_argum) == 1)
		{
			i_pc = (i_pc + 1) % MEM_SIZE;
			crnt_carr->command.argum_types[i_argum] = map[i_pc];
		}
		i_pc = (i_pc + 1) % MEM_SIZE;
		read_command_argum(crnt_carr, map, i_pc, i_argum);
		i_argum++;
	}
	return (1);
}

void do_crnt_carr(t_carriage *crnt_carr, char *map)
{
    if (crnt_carr->cnt_loop == 0)
    {
        if (read_command_frome_byte_code(crnt_carr, map) == 0)
            crnt_carr->cnt_loop = -1;
        else
        {
            crnt_carr->cnt_loop = crnt_carr->command.num_cycle;
            crnt_carr->command.num_cycle--;
        }
    }
    else if (crnt_carr->cnt_loop != -1 && crnt_carr->command.num_cycle > 0)
	    crnt_carr->command.num_cycle--;
}

void ft_corewar(t_op *frst, char *map)
{
	t_op *crnt_carr;

	crnt_carr = frst;
	while (1)
	{
		do_crnt_carr(crnt_carr, map);
		crnt_carr = crnt_carr->next;
		if (crnt_carr == NULL)
			crnt_carr = frst;
	}
}
