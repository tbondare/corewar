/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 14:25:01 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 16:27:34 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	if_fl_minus(char *newstr, t_fl_tp *lst, int sum, char neg)
{
	int res;
	int mem_w;

	mem_w = lst->wdth;
	newstr[mem_w--] = '\0';
	res = lst->wdth - sum;
	while (res)
	{
		newstr[mem_w--] = ' ';
		res--;
	}
	output_dgt(lst, newstr, &mem_w, 10);
	if (neg != 0)
		newstr[0] = neg;
}

void	if_flg_null(char *newstr, t_fl_tp *lst, int sum, char neg)
{
	int mem_w;
	int res;

	mem_w = lst->wdth;
	newstr[mem_w--] = '\0';
	output_dgt(lst, newstr, &mem_w, 10);
	res = lst->wdth - sum;
	while (res)
	{
		newstr[mem_w--] = '0';
		res--;
	}
	if (neg != 0)
		newstr[0] = neg;
}

void	if_flg_not_null(char *newstr, t_fl_tp *lst, int mem_w, char neg)
{
	newstr[mem_w--] = '\0';
	if ((lst->val.ln != 0 || lst->prc != 0 ||
				check_fl(lst->typ, g_tp_u | g_tp_ua)) && mem_w >= 0)
		output_dgt(lst, newstr, &mem_w, 10);
	if (check_fl(lst->typ, g_tp_u | g_tp_ua) && neg == '-')
	{
		neg = 0;
		while (lst->prc-- > 0)
			newstr[mem_w--] = '0';
	}
	if (neg != 0)
		newstr[mem_w--] = neg;
	while (mem_w >= 0)
		newstr[mem_w--] = ' ';
}

char	*if_wd_m_prc(t_fl_tp *lst, int num_q, int sign, char neg)
{
	char	*newstr;
	int		cnt;

	newstr = NULL;
	cnt = ft_cnt_i_d_u_ua_c(lst);
	if (!(newstr = (char*)malloc(sizeof(char) * (lst->wdth + 1))))
		return (0);
	if (check_fl(lst->flg, g_fl_min))
		if_fl_minus(newstr, lst, cnt + num_q + sign, neg);
	else
	{
		if (check_fl(lst->flg, g_fl_nll))
			if_flg_null(newstr, lst, cnt + num_q + sign, neg);
		else
			if_flg_not_null(newstr, lst, lst->wdth, neg);
	}
	return (newstr);
}
