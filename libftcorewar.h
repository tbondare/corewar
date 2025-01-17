/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftcorewar.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 20:36:53 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/16 21:38:47 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTCOREWAR_H
# define LIBFTCOREWAR_H

//# include "libft/libft.h"
//# include "libft/ft_printf/inc/libftprintf.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef char					t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

static char						g_code2t[4] = {0, T_REG, T_DIR, T_IND};
static int						g_t2size[5] = {0, 1, DIR_SIZE, 0, IND_SIZE};

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct					s_header
{
	unsigned int				magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	unsigned int				prog_size;
	char						comment[COMMENT_LENGTH + 1];
}								t_header;

typedef struct					s_command
{
	int							num_cycle;
	int							oper_code;
	int							is_arg_type;
	char						argum_types[3];
	int							argum[3];
}								t_command;

typedef	struct					s_carriage
{
	int							is_killed;
	int							next_pc;
	int							carry;
	int							reg[REG_NUMBER];
	int							num_checks;
	int							cycles_to_die;
	int							last_op_live_cycle;
	int							unic_num_carr;
	int							unic_num_plr;
	char						*file_name;
	t_header					header;
	int							pc;
	int							num_cycle_end_alive;
	t_command					command;
	int							cnt_byt_step_over;
	struct						s_carriage *next;
}								t_carriage;

typedef struct					s_vm_data
{
	t_carriage					*frst;
	t_carriage					*last_pl_said_alive;
	int							loop_num;
	int dump_num;
	int is_v_flag;
	int carg_num;
	int							cycles_to_die;
	int							num_oper_live;
	int num_checks_without_cycles_to_die_change;
	int							cnt_ccls_to_die;
}								t_vm_data;

typedef struct					s_op
{
	char						*name;
	int							argum_nums;
	char						argum_types[3];
	int							oper_code;
	int							num_cycle;
	char						*comment;
	int							cod_of_type_args;
	int							trash;
	void						(*fun)(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
}								t_op;

void							ft_oper_live(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
void							ft_oper_ld(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
void							ft_oper_st(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
void							ft_oper_add(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
void							ft_oper_sub(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
void							ft_oper_and(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
void							ft_oper_or(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
void							ft_oper_xor(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
void							ft_oper_zjmp(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
void							ft_oper_ldi(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
void							ft_oper_sti(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
void							ft_oper_fork(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
void							ft_oper_lld(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
void							ft_oper_lldi(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
void							ft_oper_lfork(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
void							ft_oper_aff(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);

static t_op						tab_op[17] =
{
	{0, 0, {0}, 0, 0, 0, 0, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, ft_oper_live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, ft_oper_ld},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, ft_oper_st},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, ft_oper_add},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, ft_oper_sub},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, ft_oper_and},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, ft_oper_or},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, ft_oper_xor},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, ft_oper_zjmp},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, ft_oper_ldi},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, ft_oper_sti},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, ft_oper_fork},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, ft_oper_lld},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, ft_oper_lldi},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, ft_oper_lfork},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, ft_oper_aff}
};

int								main(int argc, char **argv);
void free_mem(unsigned char *map, t_vm_data *data);
void							init_vm_data(t_vm_data *data);
unsigned char					*create_mem_map();

void							sorting_list_carriage(t_carriage **frst);
void swap_list_items(t_carriage **frst, t_carriage *crnt, t_carriage *mem[4]);
void	write_introduction(t_carriage *frst);

void							read_data_players(t_carriage *frst, unsigned char *map, int cnt_plr);
void	read_data_players3(t_carriage *crn, int *fd, unsigned char *map, int *cnt_plr);
void	read_data_players2(t_carriage *crn, int *fd);
int		ft_read_data_bytes(int fd);
int		ft_bytes_to_int(unsigned char *bytes, int num_bytes);

void ft_print_memory(const unsigned char *var, size_t size);
void ft_print_bytes(const unsigned char *var, int size);
void	next_line_and_print_add(int i, int size);
void	print_address(int i, const char* postfix);

int								read_inp_str(int argc, char **argv, t_vm_data *data);
int								define_next_unic_num(t_carriage *frst);
int								found_flg_min_n(char **argv, int *j, t_carriage **frst, int *cnt_plr);
int								found_same_unic_num (t_carriage **frst, int djt, int cnt_plr);
int								found_point_cor(char *file_name);

t_carriage						*add_player_to_list(t_carriage **frst, char *argv);
void							add_player_to_list_crn(t_carriage **crn, char *argv, t_carriage *frst);

int								get_arg_value(t_carriage *crnt_carr, int index_arg, unsigned char *map);
int								read_bytes(int start_address, unsigned char *map, int num_bytes);
void write_bytes_from_int(int start_address, unsigned char *map, unsigned int val);
void							change_carry(t_carriage *crnt_carr, int ind);

void							ft_corewar(unsigned char *map, t_vm_data *data);
void	if_loop_num_q_dump_num(unsigned char *map, t_vm_data *data);
void	print_chemp_name(t_vm_data *data);

void							do_crnt_carr(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);
void							do_check(t_carriage *crnt_carr, t_vm_data *data);
void							check_alive(t_carriage *crnt_carr, t_vm_data *data);
void							do_command(t_carriage *crnt_carr, unsigned char *map, t_vm_data *data);

int								read_command_frome_byte_code(t_carriage *crnt_carr, unsigned char *map);
void							read_arg_types(t_carriage *crnt_carr, unsigned char *map);
int								is_val_arg_tapes(t_op *info_com, t_carriage *crnt_carr);
int								read_com_argums(t_op *info_com, t_carriage *crnt_carr, unsigned char *map);
void							read_command_argum(t_carriage *crnt_carr, unsigned char *map, int i_argum);

int								is_val_command_oper_code(int crnt_oper_code);
int								is_argum_type(t_op *info_com, t_carriage *crnt_carr);

void	copy_carr(t_carriage *crnt_carr, t_vm_data *data, int new_pc);
int		ft_atoi_strict(char const *str);

#endif
