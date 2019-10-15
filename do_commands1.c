#include "libftcorewar.h"

int read_bytes(int start_address, char *map, int num_bytes)
{
	char bytes[4];
	int i;

	i = 0;
	ft_bzero(bytes, 4);
	while (i < num_bytes)
	{
		bytes[i] = map[start_address];
		start_address = (start_address + 1) % MEM_SIZE;
		i++;
	}
	i = 0;
	ft_memcpy(&i, &bytes[0], num_bytes);
	i = i >> ((sizeof(int) - num_bytes) * 8);
	return (i);
}

void write_bytes(int start_address, int value, char *map)
{
	int i;

	i = 0;
	while (i < 4)
	{
		map[start_address] = ((char*)(&value))[i];
		start_address = (start_address + 1) % MEM_SIZE;
		i++;
	}
}

void change_carry(t_carriage *crnt_carr, int ind)
{
	if (crnt_carr->reg[crnt_carr->command.argum[ind]] == 0)
		crnt_carr->carry = 1;
	else
		crnt_carr->carry = 0;
}

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
	int address;

	if (crnt_carr->command.argum_types[0] == T_DIR)
		crnt_carr->reg[crnt_carr->command.argum[1]] = crnt_carr->command.argum[0];
	else if(crnt_carr->command.argum_types[0] == T_IND)
	{
		address = crnt_carr->command.argum[0] % IDX_MOD + crnt_carr->pc;
		crnt_carr->reg[crnt_carr->command.argum[1]]
		= read_bytes(address, map, sizeof(int));
	}
	change_carry(crnt_carr, 1);
}

void ft_oper_st(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	if (crnt_carr->command.argum_types[1] == T_REG)
		crnt_carr->reg[crnt_carr->command.argum[0]]
		= crnt_carr->reg[crnt_carr->command.argum[1]];
	else if (crnt_carr->command.argum_types[1] == T_IND)
	{
		write_bytes(crnt_carr->command.argum[1] % IDX_MOD + crnt_carr->pc,
				crnt_carr->command.argum[0], map);
	}
}

void ft_oper_add(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	crnt_carr->reg[crnt_carr->command.argum[2]] =
			crnt_carr->reg[crnt_carr->command.argum[0]]
			+ crnt_carr->reg[crnt_carr->command.argum[1]];
	change_carry(crnt_carr, 2);
}

void ft_oper_sub(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	crnt_carr->reg[crnt_carr->command.argum[2]] =
			crnt_carr->reg[crnt_carr->command.argum[0]]
			- crnt_carr->reg[crnt_carr->command.argum[1]];
	change_carry(crnt_carr, 2);
}

int get_arg_value(t_carriage *crnt_carr, int index_arg, char *map)
{
	if (crnt_carr->command.argum_types[index_arg] == T_REG)
		return (crnt_carr->reg[crnt_carr->command.argum[index_arg]]);
	if (crnt_carr->command.argum_types[index_arg] == T_DIR)
		return (crnt_carr->command.argum[index_arg]);
	if (crnt_carr->command.argum_types[index_arg] == T_IND)
		return (read_bytes(crnt_carr->command.argum[index_arg]
		% IDX_MOD + crnt_carr->pc, map, 4));
}

void ft_oper_and(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	crnt_carr->reg[crnt_carr->command.argum[2]] = get_arg_value(crnt_carr, 0, map)
			& get_arg_value(crnt_carr, 1, map);
	change_carry(crnt_carr, 2);
}

void ft_oper_or(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	crnt_carr->reg[crnt_carr->command.argum[2]] = get_arg_value(crnt_carr, 0, map)
			| get_arg_value(crnt_carr, 1, map);
	change_carry(crnt_carr, 2);
}

void ft_oper_xor(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	crnt_carr->reg[crnt_carr->command.argum[2]] = get_arg_value(crnt_carr, 0, map)
			^ get_arg_value(crnt_carr, 1, map);
	change_carry(crnt_carr, 2);
}

void ft_oper_zjmp(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	if (crnt_carr->carry == 1)
		crnt_carr->pc = crnt_carr->pc + crnt_carr->command.argum[0] % IDX_MOD;
}

void ft_oper_ldi(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	crnt_carr->reg[crnt_carr->command.argum[2]] =
			read_bytes(crnt_carr->pc + (get_arg_value(crnt_carr, 0, map)
			+ get_arg_value(crnt_carr, 1, map)) % IDX_MOD, map, 4);
}

void ft_oper_sti(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	write_bytes(crnt_carr->pc + (get_arg_value(crnt_carr, 1, map)
	+ get_arg_value(crnt_carr, 2, map)) % IDX_MOD,
			crnt_carr->reg[crnt_carr->command.argum[0]], map);
}

void copy_carr(t_carriage *crnt_carr, t_vm_data *data, int new_pc)
{
	t_carriage *new_carr;

	new_carr = (t_carriage *)malloc(sizeof(t_carriage));
	ft_memcpy(new_carr->reg, crnt_carr->reg, sizeof(int) * REG_NUMBER);
	new_carr->unic_num_plr = crnt_carr->unic_num_plr;
	new_carr->file_name = crnt_carr->file_name;
	new_carr->command.num_cycle = crnt_carr->command.num_cycle;
	new_carr->cycles_to_die = crnt_carr->cycles_to_die;
	new_carr->num_checks = crnt_carr->num_checks;
	new_carr->cnt_ccls_to_die = crnt_carr->cnt_ccls_to_die;
	new_carr->command.is_arg_type = crnt_carr->command.is_arg_type;
	new_carr->num_oper_live = crnt_carr->num_oper_live;
	new_carr->num_cycle_end_alive = crnt_carr->num_cycle_end_alive;
	new_carr->carry = crnt_carr->carry;
	new_carr->next = data->frst;
	data->frst = new_carr;
	new_carr->pc = new_pc % MEM_SIZE;
}

void ft_oper_fork(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	copy_carr(crnt_carr, data, crnt_carr->pc + crnt_carr->command.argum[0] % IDX_MOD);
}

void ft_oper_lld(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	int address;

	if (crnt_carr->command.argum_types[0] == T_DIR)
		crnt_carr->reg[crnt_carr->command.argum[1]] = crnt_carr->command.argum[0];
	else if(crnt_carr->command.argum_types[0] == T_IND)
	{
		address = crnt_carr->command.argum[0] + crnt_carr->pc;
		crnt_carr->reg[crnt_carr->command.argum[1]]
				= read_bytes(address, map, sizeof(int));
	}
	change_carry(crnt_carr, 1);
}

void ft_oper_lldi(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	crnt_carr->reg[crnt_carr->command.argum[2]]
	= read_bytes(crnt_carr->pc + (get_arg_value(crnt_carr, 0, map)
			+ get_arg_value(crnt_carr, 1, map)), map, 4);
}

void ft_oper_lfork(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	copy_carr(crnt_carr, data, crnt_carr->pc + crnt_carr->command.argum[0]);
}

void ft_oper_aff(t_carriage *crnt_carr, char *map, t_vm_data *data)
{
	write(1, &crnt_carr->reg[crnt_carr->command.argum[0]], 1);
}