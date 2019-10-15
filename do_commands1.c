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

void ft_oper_ld(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	if(crnt_carr->command.argum_types == )
}

void ft_oper_st(t_carriage *crnt_carr, char *map, t_vm_data *data)
{

}
void ft_oper_add(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	crnt_carr->reg[crnt_carr->command.argum[2]] =
			crnt_carr->reg[crnt_carr->command.argum[0]]
			+ crnt_carr->reg[crnt_carr->command.argum[1]];
	if (crnt_carr->reg[crnt_carr->command.argum[2]] == 0)
		crnt_carr->carry = 1;
	else
		crnt_carr->carry = 0;
}
void ft_oper_sub(t_carriage *crnt_carr, char *map, t_vm_data *data)
{

}
void ft_oper_and(t_carriage *crnt_carr, char *map, t_vm_data *data)
{

}
void ft_oper_or(t_carriage *crnt_carr, char *map, t_vm_data *data)
{

}
void ft_oper_xor(t_carriage *crnt_carr, char *map, t_vm_data *data)
{

}
void ft_oper_zjmp(t_carriage *crnt_carr, char *map, t_vm_data *data)
{

}
void ft_oper_ldi(t_carriage *crnt_carr, char *map, t_vm_data *data)
{

}
void ft_oper_sti(t_carriage *crnt_carr, char *map, t_vm_data *data)
{

}
void ft_oper_fork(t_carriage *crnt_carr, char *map, t_vm_data *data)
{

}
void ft_oper_lld(t_carriage *crnt_carr, char *map, t_vm_data *data)
{

}
void ft_oper_lldi(t_carriage *crnt_carr, char *map, t_vm_data *data)
{

}
void ft_oper_lfork(t_carriage *crnt_carr, char *map, t_vm_data *data)
{

}
void ft_oper_aff(t_carriage *crnt_carr, char *map, t_vm_data *data)
{

}