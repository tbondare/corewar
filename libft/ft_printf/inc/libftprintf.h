/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:44:00 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/04 20:37:55 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <inttypes.h>
# include <stdarg.h>
# include <wchar.h>
# include <locale.h>

typedef struct			s_val
{
	long long			ln;
	unsigned long long	uln;
	void				*pnt;
	intmax_t			imx;
	uintmax_t			uimx;
	char				*str;
	long double			lndbl;
	wint_t				win;
}						t_val;

typedef struct			s_fl_tp
{
	char				*str_out;
	int					ind_arg;
	int					flg;
	int					wdth;
	int					prc;
	int					md_len;
	int					typ;
	char				wdth_star;
	char				prc_star;
	int					ind_arg_wdth;
	int					ind_arg_prc;
	t_val				val;
	int					mem;
	struct s_fl_tp		*next;
}						t_fl_tp;

typedef struct			s_arr
{
	char				flg_or_tp_or_ln;
	unsigned int		bit_flg;
}						t_arr;

static const char		g_ar_frst = ' ';
static const char		g_ar_not = 0;
static const char		g_ar_fl = 1;
static const char		g_ar_tp = 2;
static const char		g_ar_ln = 3;

static const int		g_fl_pls = 1;
static const int		g_fl_min = 2;
static const int		g_fl_nll = 4;
static const int		g_fl_grl = 8;
static const int		g_fl_spc = 16;
static const int		g_fl_quo = 32;

static const int		g_ln_la = 1;
static const int		g_ln_hh = 2;
static const int		g_ln_h = 4;
static const int		g_ln_l = 8;
static const int		g_ln_ll = 16;
static const int		g_ln_j = 32;
static const int		g_ln_z = 64;

static const int		g_tp_s = 1;
static const int		g_tp_sa = 2;
static const int		g_tp_p = 4;
static const int		g_tp_d = 8;
static const int		g_tp_da = 16;
static const int		g_tp_i = 32;
static const int		g_tp_o = 64;
static const int		g_tp_oa = 128;
static const int		g_tp_u = 256;
static const int		g_tp_ua = 512;
static const int		g_tp_x = 1024;
static const int		g_tp_xa = 2048;
static const int		g_tp_c = 4096;
static const int		g_tp_ca = 8192;
static const int		g_tp_e = 16384;
static const int		g_tp_ea = 32768;
static const int		g_tp_f = 65536;
static const int		g_tp_fa = 131072;
static const int		g_tp_g = 262144;
static const int		g_tp_ga = 524288;
static const int		g_tp_a = 1048576;
static const int		g_tp_aa = 2097152;
static const int		g_tp_n = 4194304;
static const int		g_tp_b = 8388608;
static const int		g_tp_r = 16777216;
static const int		g_tp_k = 33554432;
static const int		g_tp_pct = 67108864;
static const int		g_tp_err = 134217728;

void					init_arr(t_arr *arr);
void					init_types_2(t_arr *arr);
void					init_types_1(t_arr *arr);
void					init_length(t_arr *arr);
void					init_flags(t_arr *arr);

void					determine_md_len(const char *frmt,
		int *i, t_fl_tp *lst, t_arr *arr);
void					determine_width(const char *frmt, int *i, t_fl_tp *lst);
void					determine_precision(const char *frmt,
		int *i, t_fl_tp *lst);
void					determine_dgt_data(const char *frmt,
		int *i, t_fl_tp *lst);
char					*create_dgt_str(const char *frmt, int *i);

int						fill_struct(t_fl_tp **prm, const char *frmt);
void					index_args (t_fl_tp *lst);
void					lstnewadd(t_fl_tp **lst);
void					fill_element(t_fl_tp **lst, const char *frmt, int *i);
void					ft_while_determ(t_fl_tp *lst, const char *frmt,
		int *i, t_arr *arr);

unsigned int			set_flg(unsigned int flags, unsigned int flg);
int						check_fl(unsigned int flags, unsigned int flg);
t_fl_tp					*lstnew(void);
char					*rejoin(char *s1, const char c);
char					*ft_strchar(char const *s1, char const c);

void					determ_args_d_i(t_fl_tp *lst, va_list args);
void					determ_args_o_u_x_xa(t_fl_tp *lst, va_list args);
void					determ_args_n(t_fl_tp *lst, va_list args);
void					dtrm_args_with_if(t_fl_tp *lst, va_list args);
void					else_determ(t_fl_tp *lst, va_list args);

void					determine_args(t_fl_tp *prm, va_list args);
void					ft_if_detetm (t_fl_tp *lst, va_list args,
		va_list *next, int *i);
int						cnt_args(t_fl_tp *lst);

void					outp_id_j(t_fl_tp *lst, char *newstr, int *mem_w);
void					outp_uox_xa_j(t_fl_tp *lst, char *newstr,
		int *mem_w, int base);
void					outp_id_da(t_fl_tp *lst, char *newstr, int *mem_w);
void					outp_c_l(t_fl_tp *lst, char *newstr, int *mem_w);
void					outp_uua_ooa_xxa(t_fl_tp *lst, char *newstr,
		int *mem_w, int base);

int						ft_cnt_i_d_u_ua_c(t_fl_tp *lst);
int						cnt_u_ua(t_fl_tp *lst, int *cnt);
int						cnt_u_j(t_fl_tp *lst, int *cnt);
int						cnt_id_j(t_fl_tp *lst, int *cnt);
int						cnt_id_da(t_fl_tp *lst, int *cnt);

int						cnt_p(t_fl_tp *lst, int *cnt, int base);

void					determine_args(t_fl_tp *prm, va_list args);
int						cnt_args(t_fl_tp *lst);
void					ft_if_detetm(t_fl_tp *lst, va_list args,
		va_list *next, int *i);
void					if_prc_min_one(t_fl_tp	**lst, va_list args,
		va_list *next, int *i);

int						ft_printf(const char *format, ...);
int						printing_args(t_fl_tp *prm, int *total_strlen);
void					print_str(char *str);

void					if_f_tp_c(t_fl_tp *lst, int *mem_w, char sgn);
int						if_print_args(t_fl_tp *lst, char **str);
int						if_print_args2(t_fl_tp *lst, char **str,
		int *total_strlen);
int						if_print_args3(t_fl_tp *lst, char **str, int *mem_w);
int						if_str_nul(t_fl_tp **lst, char **str,
		int *total_strlen, int *mem_w);

char					*if_quote(char *arr, int *cnt, int *i, int *j);
char					*quote(char *arr, int cnt);
int						cnt_till_aa_ee_ff_gg(int base, long double *mem_val,
		t_fl_tp *lst);
int						check_is_sign_in_float(t_fl_tp *lst, char *neg);

char					*outp_float(t_fl_tp *lst, int num_dgt,
		int cnt, long double *mem_val);
char					*if_op_fl(t_fl_tp *lst, int *num_dgt,
		int *mem_cnt, int *i);
void					if_dgt_more_five(int dgt, char *arr,
		int i, struct lconv *lc);
int						while_if(long double *mem_val,
		int *mem_cnt, char *arr, int *i);

char					*itoa_aaa_eea_ffa_gga(t_fl_tp *lst);

void					output_dgt(t_fl_tp *lst, char *newstr,
		int *mem_w, int base);
int						num_qv(t_fl_tp *lst, int cnt);
int						check_is_sign(t_fl_tp *lst, char *neg);
int						check_sign_dif_tp(t_fl_tp *lst);

char					*itoa_printf(t_fl_tp *lst);
char					*if_fl_min_wdth_m_prc(t_fl_tp *lst, int sign, char neg);
char					*if_prcsig_m_wd(t_fl_tp *lst, int sign, char neg);
char					*if_itoa_printf(t_fl_tp *lst, int num_q,
		int sign, char neg);
char					*if_itoa_printf1(t_fl_tp *lst, int num_q,
		int sign, char neg);

char					*if_wd_m_prc(t_fl_tp *lst, int num_q,
		int sign, char neg);
void					if_flg_not_null (char *newstr, t_fl_tp *lst,
		int mem_w, char neg);
void					if_flg_null(char *newstr, t_fl_tp *lst,
		int sum, char neg);
void					if_fl_minus(char *newstr, t_fl_tp *lst,
		int sum, char neg);

char					*itoa_printf_ooa_xxa_b(t_fl_tp *lst);
char					*if_prc_m_wd(t_fl_tp *lst, int base, char *newstr);
void					if_lg_min(t_fl_tp *lst, char *newstr,
		int base, int cnt);
char					*if_f_prc_nul(t_fl_tp *lst, char *newstr,
		int cnt, int base);
char					*itoa_o_x_b(t_fl_tp *lst, int *base,
		int *cnt, char *newstr);

void					if_flg_not_null_oxb(char *newstr, t_fl_tp *lst,
		int base);
void					if_flg_null_ooxxb(char *newstr, t_fl_tp *lst,
		int cnt, int base);
void					if_fl_grill(t_fl_tp *lst, char *newstr, int *mem_w);
void					if_fl_minus_ooxxb(char *newstr, t_fl_tp *lst,
		int cnt, int base);
char					*if_val_null(char *newstr);

int						ft_cnt_oo_xx_b(t_fl_tp *lst, int base);
int						cnt_ox_xa(t_fl_tp *lst, int *cnt, int base);
int						cnt_ox_xa_j(t_fl_tp *lst, int *cnt, int base);
int						cnt_p(t_fl_tp *lst, int *cnt, int base);
void					outp_p(t_fl_tp *lst, char *newstr,
		int *mem_w, int base);

char					*print_cca_ssa(t_fl_tp *lst);

char					*if_tp_c(t_fl_tp *lst, char *newstr, char sgn, int i);
char					*if_wd_m_prc_c(t_fl_tp *lst,
		char *newstr, char sgn, int *i);
char					*else_f_pt_s(t_fl_tp *lst, char *newstr,
		char sgn, int *i);
char					*if_tp_s_str_n_nul(t_fl_tp *lst,
		char *newstr, int i, char sgn);
char					*str_null(t_fl_tp *lst, char *newstr, int i, char sgn);

char					*print_unicode(t_fl_tp *lst);
char					*if_wd_m_cnt(t_fl_tp *lst, char *allstr,
		char *str, int mem_cnt);
int						ft_memory(t_fl_tp *lst, char **str);
char					*ft_else_tp_s(t_fl_tp *lst, char *str,
		int cnt, int *mem_cnt);
char					*ft_else_if_pr_un(t_fl_tp *lst, char *str, int cnt);

void					bin_op_for_unicode(t_fl_tp *lst,
		int *cnt, int i, char *str);
void					uf_in_ucod(int *cnt, wchar_t wc, char *str);

char					*print_pct(t_fl_tp *lst);
void					ft_if_print_pct(t_fl_tp *lst, char *str, int *i);

void					*ft_memset(void *b, int c, size_t len);
char					*ft_strdup(const char *s1);
size_t					ft_strlen(const char *str);
char					*ft_strjoin(char const *s1, char const *s2);
void					ft_bzero(void *s, size_t n);
void					ft_strdel(char **as);
int						ft_isspace(int c);
char					*ft_strnew(size_t size);
int						ft_atoi(const char *str);

#endif
