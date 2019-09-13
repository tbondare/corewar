
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

/*
**
*/

typedef struct s_registers
{
    int live;
    int ld;
    int st;
    int add;
    int sub;
    int and;
    int or;
    int xor;
    int zjmp;
    int ldi;
    int sti;
    int fork;
    int lld;
    int lldi;
    int lfork;
    int aff;
}t__registers;

typedef struct s_carriage
{
	int unic_num;
	char *file_name;
	header_t header;
	int pc;
	int u_num_carr;
	int carry;
	int crn_cod_oper;
	int num_cycle_end_alive;
	int remaining_cycles;
	struct s_carrige *crn_position;
    int cnt_byt_step_over;

	struct s_carriage *next;
}t_carriage;

void read_data_players(t_carriage *frst, char *map, int cnt_plr);
char *create_mem_map();
void init_map(char **map, t_carriage *frst);
void ft_corewar(t_carriage *frst, char **map);

#endif