/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:07:31 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 15:57:19 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_while_determ(t_fl_tp *lst, const char *frmt, int *i, t_arr *arr)
{
	while (frmt[*i] != '\0')
	{
		if (frmt[*i] > '0' && frmt[*i] <= '9')
			determine_dgt_data(frmt, i, lst);
		else if (frmt[*i] == '*')
			determine_width(frmt, i, lst);
		else if (frmt[*i] == '.')
			determine_precision(frmt, i, lst);
		else if (arr[frmt[*i] - g_ar_frst].flg_or_tp_or_ln == g_ar_fl)
			(lst)->flg = set_flg(lst->flg, arr[frmt[*i] - g_ar_frst].bit_flg);
		else if (arr[frmt[*i] - g_ar_frst].flg_or_tp_or_ln == g_ar_ln)
			determine_md_len(frmt, i, lst, arr);
		else if (arr[frmt[*i] - g_ar_frst].flg_or_tp_or_ln == g_ar_tp)
		{
			(lst)->typ = set_flg((lst)->typ, arr[frmt[*i] - g_ar_frst].bit_flg);
			return ;
		}
		else
		{
			lst->typ = set_flg(lst->typ, g_tp_err);
			lst->val.uln = frmt[*i];
			return ;
		}
		(*i)++;
	}
}

void	fill_element(t_fl_tp **lst, const char *frmt, int *i)
{
	static t_arr	arr[91];
	static char		init = 0;

	(*i)++;
	if (init == 0)
	{
		init_arr(arr);
		init = 1;
	}
	if (frmt[*i] == '%')
	{
		if (frmt[*i + 1] != '\0')
			lstnewadd(lst);
		(*lst)->str_out = rejoin((*lst)->str_out, '%');
		return ;
	}
	if (ft_strlen((*lst)->str_out) != 0 || (*lst)->typ != 0)
		lstnewadd(lst);
	ft_while_determ(*lst, frmt, i, arr);
}

void	lstnewadd(t_fl_tp **lst)
{
	(*lst)->next = lstnew();
	*lst = (*lst)->next;
}

void	index_args(t_fl_tp *lst)
{
	int cnt;

	cnt = 1;
	while (lst)
	{
		if (lst->wdth_star == '*' && lst->wdth >= 0)
		{
			lst->ind_arg_wdth = cnt;
			cnt++;
		}
		if (lst->prc_star == '*' && lst->prc == -1)
		{
			lst->ind_arg_prc = cnt;
			cnt++;
		}
		if (lst->ind_arg == 0 && lst->typ != 0)
		{
			lst->ind_arg = cnt;
			cnt++;
		}
		lst = lst->next;
	}
}

int		fill_struct(t_fl_tp **prm, const char *frmt)
{
	int		i;
	t_fl_tp	*lst;

	i = 0;
	if (!(*prm = lstnew()))
		return (0);
	lst = *prm;
	while (frmt[i] != '\0')
	{
		if (frmt[i] == '%' && frmt[i + 1] == '\0')
			return (0);
		else if (frmt[i] == '%' && frmt[i + 1] != '\0')
			fill_element(&lst, frmt, &i);
		else
		{
			if (lst->typ != 0)
				lstnewadd(&lst);
			lst->str_out = rejoin(lst->str_out, frmt[i]);
		}
		i++;
	}
	index_args(*prm);
	return (1);
}
