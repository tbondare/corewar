
#ifndef LIBFTCOREWAR_H
#define LIBFTCOREWAR_H

#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

static char code2t[4] = {0, T_REG, T_DIR, T_IND};
static int t2size[5] = {0, REG_SIZE, DIR_SIZE, 0, IND_SIZE};

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		header_s
{
    unsigned int		magic;
    char				prog_name[PROG_NAME_LENGTH + 1];
    unsigned int		prog_size;
    char				comment[COMMENT_LENGTH + 1];
}					header_t;

typedef struct s_command
{
	int num_cycle;
	int oper_code;
	int is_arg_type;
	char argum_types[3];
	int argum[3];
}t_command;

typedef struct s_carriage
{
	int reg[REG_NUMBER];
	int num_checks;
	int cnt_ccls_to_die;
	int cycles_to_die;
	int num_oper_live;
	int unic_num_carr;
	int unic_num_plr;
	char *file_name;
	header_t header;
	int pc;
	int num_cycle_end_alive;
	t_command command;
	int cnt_byt_step_over;
	struct s_carriage *next;
}t_carriage;

typedef struct s_vm_data
{
	t_carriage *frst;
	t_carriage *last_pl_said_alive;
	int loop_num;
}t_vm_data;

typedef struct s_op
{
	char *name;
	int argum_nums;
	char argum_types[3];
	int oper_code;
	int num_cycle;
	char *comment;
	int cod_of_type_args;
	void (*fun)(t_carriage *crnt_carr, char *map, t_vm_data *data);

}t_op;

void ft_oper_live(t_carriage *crnt_carr, char *map, t_vm_data *data);

static t_op   op_tab[17] =
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

/*
**
*/

void read_data_players(t_carriage *frst, char *map, int cnt_plr);
char *create_mem_map();
void init_map(char **map, t_carriage *frst);
void ft_corewar(char *map, t_vm_data *data);

#endif
