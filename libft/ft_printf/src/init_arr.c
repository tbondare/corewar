/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:09:38 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/02 19:13:10 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	init_flags(t_arr *arr)
{
	arr['+' - g_ar_frst].flg_or_tp_or_ln = g_ar_fl;
	arr['+' - g_ar_frst].bit_flg = g_fl_pls;
	arr['-' - g_ar_frst].flg_or_tp_or_ln = g_ar_fl;
	arr['-' - g_ar_frst].bit_flg = g_fl_min;
	arr['0' - g_ar_frst].flg_or_tp_or_ln = g_ar_fl;
	arr['0' - g_ar_frst].bit_flg = g_fl_nll;
	arr['#' - g_ar_frst].flg_or_tp_or_ln = g_ar_fl;
	arr['#' - g_ar_frst].bit_flg = g_fl_grl;
	arr[' ' - g_ar_frst].flg_or_tp_or_ln = g_ar_fl;
	arr[' ' - g_ar_frst].bit_flg = g_fl_spc;
	arr['\'' - g_ar_frst].flg_or_tp_or_ln = g_ar_fl;
	arr['\'' - g_ar_frst].bit_flg = g_fl_quo;
}

void	init_length(t_arr *arr)
{
	arr['L' - g_ar_frst].flg_or_tp_or_ln = g_ar_ln;
	arr['L' - g_ar_frst].bit_flg = g_ln_la;
	arr['h' - g_ar_frst].flg_or_tp_or_ln = g_ar_ln;
	arr['h' - g_ar_frst].bit_flg = g_ln_h;
	arr['l' - g_ar_frst].flg_or_tp_or_ln = g_ar_ln;
	arr['l' - g_ar_frst].bit_flg = g_ln_l;
	arr['j' - g_ar_frst].flg_or_tp_or_ln = g_ar_ln;
	arr['j' - g_ar_frst].bit_flg = g_ln_j;
	arr['z' - g_ar_frst].flg_or_tp_or_ln = g_ar_ln;
	arr['z' - g_ar_frst].bit_flg = g_ln_z;
}

void	init_types_1(t_arr *arr)
{
	arr['s' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['s' - g_ar_frst].bit_flg = g_tp_s;
	arr['S' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['S' - g_ar_frst].bit_flg = g_tp_sa;
	arr['p' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['p' - g_ar_frst].bit_flg = g_tp_p;
	arr['d' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['d' - g_ar_frst].bit_flg = g_tp_d;
	arr['D' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['D' - g_ar_frst].bit_flg = g_tp_da;
	arr['i' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['i' - g_ar_frst].bit_flg = g_tp_i;
	arr['o' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['o' - g_ar_frst].bit_flg = g_tp_o;
	arr['O' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['O' - g_ar_frst].bit_flg = g_tp_oa;
	arr['u' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['u' - g_ar_frst].bit_flg = g_tp_u;
	arr['U' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['U' - g_ar_frst].bit_flg = g_tp_ua;
	arr['x' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['x' - g_ar_frst].bit_flg = g_tp_x;
	arr['X' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['X' - g_ar_frst].bit_flg = g_tp_xa;
}

void	init_types_2(t_arr *arr)
{
	arr['c' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['c' - g_ar_frst].bit_flg = g_tp_c;
	arr['C' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['C' - g_ar_frst].bit_flg = g_tp_ca;
	arr['e' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['e' - g_ar_frst].bit_flg = g_tp_e;
	arr['E' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['E' - g_ar_frst].bit_flg = g_tp_ea;
	arr['f' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['f' - g_ar_frst].bit_flg = g_tp_f;
	arr['F' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['F' - g_ar_frst].bit_flg = g_tp_fa;
	arr['g' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['g' - g_ar_frst].bit_flg = g_tp_g;
	arr['G' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['G' - g_ar_frst].bit_flg = g_tp_ga;
	arr['a' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['a' - g_ar_frst].bit_flg = g_tp_a;
	arr['A' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['A' - g_ar_frst].bit_flg = g_tp_aa;
	arr['n' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['n' - g_ar_frst].bit_flg = g_tp_n;
}

void	init_arr(t_arr *arr)
{
	int i;

	i = 0;
	while (i < 91)
	{
		arr[i].flg_or_tp_or_ln = g_ar_not;
		i++;
	}
	init_flags(arr);
	init_length(arr);
	init_types_1(arr);
	init_types_2(arr);
	arr['b' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['b' - g_ar_frst].bit_flg = g_tp_b;
	arr['r' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['r' - g_ar_frst].bit_flg = g_tp_r;
	arr['k' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['k' - g_ar_frst].bit_flg = g_tp_k;
	arr['%' - g_ar_frst].flg_or_tp_or_ln = g_ar_tp;
	arr['%' - g_ar_frst].bit_flg = g_tp_pct;
}
