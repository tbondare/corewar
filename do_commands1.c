#include "libftcorewar.h"

void ft_oper_live(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	if (crnt_carr->command.argum[0] == -crnt_carr->unic_num_plr)
	{
		crnt_carr->num_cycle_end_alive = data->loop_num;
		data->last_pl_said_alive = crnt_carr;
		crnt_carr->num_oper_live++;
	}
}
