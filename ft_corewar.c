
#include "libftcorewar.h"

int is_val_command_oper_code(int crnt_oper_code)
{
    if (crnt_oper_code > 0 && crnt_oper_code < 17)
        return (1);
    else
        return (0);
}

int is_argum_type(t_op *info_com, t_carriage *crnt_carr)
{
    if (info_com->argum_nums == 1 && info_com->argum_types[0] == T_DIR)
    {
        crnt_carr->command.is_arg_type = 0;
        return (0);
    }
    else
        return (1);
}

void read_command_argum(t_carriage *crnt_carr, char *map, int i_argum)
{
	int crnt_arg_size;

	crnt_arg_size = t2size[crnt_carr->command.argum_types[i_argum]];
	crnt_carr->command.argum[i_argum] = 0;
	crnt_carr->command.argum[i_argum]
}

void read_com_argums(t_op *info_com, t_carriage *crnt_carr, char *map)
{
	int i_argum;

	i_argum = 0;
	read_command_argum(crnt_carr, map, i_argum);
	while (i_argum < info_com->argum_nums)
	{
		crnt_carr->pc = (crnt_carr->pc + 1) % MEM_SIZE;
		read_command_argum(crnt_carr, map, i_argum);
		i_argum++;
	}
}

int is_val_arg_tapes(t_op *info_com, t_carriage *crnt_carr)
{
    int i;

    i = 0;
    while (i < info_com->argum_nums)
    {
		if (!(crnt_carr->command.argum_types[i] & info_com->argum_types[i]
		== crnt_carr->command.argum_types[i]))
			return (0);
        i++;
    }
    return (1);
}

void read_arg_types(t_carriage *crnt_carr, char *map)
{
	char crnt_byte;

	crnt_carr->pc = (crnt_carr->pc + 1) % MEM_SIZE;
	crnt_byte = map[crnt_carr->pc];
	crnt_carr->command.argum_types[0] = code2t[crnt_byte >> 6];
	crnt_carr->command.argum_types[1] = code2t[(crnt_byte << 2) >> 6];
	crnt_carr->command.argum_types[2] = code2t[(crnt_byte << 4) >> 6];
}

int read_command_frome_byte_code(t_carriage *crnt_carr, char *map)
{
	t_op *info_com;

	crnt_carr->command.oper_code = map[crnt_carr->pc];
	if (is_val_command_oper_code(crnt_carr->command.oper_code) != 1)
	{
		crnt_carr->pc = (crnt_carr->pc + 1) % MEM_SIZE;
		return (0);
	}
	info_com = &op_tab[crnt_carr->command.oper_code];
	crnt_carr->command.num_cycle = info_com->num_cycle - 1;
	if (is_argum_type(info_com, crnt_carr) != 0)
    {
		read_arg_types(crnt_carr, map);
        if (is_val_arg_tapes(info_com, crnt_carr) != 0)
        	crnt_carr->pc = (crnt_carr->pc + 1) % MEM_SIZE;
		else
			return (0);
    }
	read_com_argums(info_com, crnt_carr, map);
	return (1);
}

void do_command(t_carriage *crnt_carr, char *map)
{

}

void do_crnt_carr(t_carriage *crnt_carr, char *map)
{
    if (crnt_carr->command.num_cycle == -1)
    {
        if (read_command_frome_byte_code(crnt_carr, map) == 0)
            crnt_carr->command.num_cycle = -1;
        else
        {
        	if (crnt_carr->command.num_cycle > 0)
            	crnt_carr->command.num_cycle--;
        }
        if (crnt_carr->command.num_cycle == 0)
			do_command(crnt_carr, map);
    }
    else
	{
		if (crnt_carr->command.num_cycle > 0)
			crnt_carr->command.num_cycle--;
		else
		{
			do_command(crnt_carr, map);
			crnt_carr->command.num_cycle = -1;
		}
	}
}

void ft_corewar(t_carriage *frst, char *map)
{
	t_carriage *crnt_carr;

	crnt_carr = frst;
	while (1)
	{
		do_crnt_carr(crnt_carr, map);
		crnt_carr = crnt_carr->next;
		if (crnt_carr == NULL)
			crnt_carr = frst;
	}
}
