/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 18:03:08 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/02 19:11:56 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*if_fl_min_wdth_m_prc(t_fl_tp *lst, int sign, char neg)
{
	char	*newstr;
	int		mem_w;
	int		res;

	newstr = NULL;
	mem_w = lst->wdth;
	if (!(newstr = (char*)malloc(sizeof(char) * (lst->wdth + 1))))
		return (0);
	newstr[mem_w--] = '\0';
	res = lst->wdth - lst->prc - sign;
	while (res)
	{
		newstr[mem_w--] = ' ';
		res--;
	}
	output_dgt(lst, newstr, &mem_w, 10);
	if (neg != 0)
		newstr[0] = neg;
	else
		newstr[0] = '0';
	return (newstr);
}

char	*if_prcsig_m_wd(t_fl_tp *lst, int sign, char neg)
{
	char	*newstr;
	int		mem_w;

	newstr = NULL;
	mem_w = lst->prc + sign;
	if (!(newstr = (char*)malloc(sizeof(char) * (lst->prc + sign + 1))))
		return (0);
	newstr[mem_w--] = '\0';
	output_dgt(lst, newstr, &mem_w, 10);
	if (neg != 0)
		newstr[mem_w] = neg;
	else if (mem_w >= 0)
		newstr[mem_w] = '0';
	return (newstr);
}

char	*if_itoa_printf(t_fl_tp *lst, int num_q, int sign, char neg)
{
	char	*newstr;
	int		cnt;

	newstr = NULL;
	cnt = ft_cnt_i_d_u_ua_c(lst);
	if (lst->prc == 0 && check_fl(lst->typ, g_tp_d | g_tp_da | g_tp_i) &&
			lst->val.ln == 0 && lst->wdth == 0)
	{
		if (!(newstr = (char*)malloc(sizeof(char) * 1)))
			return (0);
		newstr[0] = '\0';
	}
	else if (lst->wdth > cnt + num_q + sign &&
			lst->prc <= cnt + num_q && lst->wdth > lst->prc)
		newstr = if_wd_m_prc(lst, num_q, sign, neg);
	else if (lst->wdth <= cnt + sign + num_q && lst->prc <= cnt + num_q)
	{
		if (!(newstr = (char*)malloc(sizeof(char) * (cnt + sign + num_q + 1))))
			return (0);
		if_flg_not_null(newstr, lst, cnt + sign + num_q, neg);
	}
	else if (lst->prc + sign >= lst->wdth)
		newstr = if_prcsig_m_wd(lst, sign, neg);
	return (newstr);
}

char	*if_itoa_printf1(t_fl_tp *lst, int num_q, int sign, char neg)
{
	char	*newstr;
	int		cnt;

	newstr = NULL;
	cnt = ft_cnt_i_d_u_ua_c(lst);
	if (lst->wdth > cnt + num_q + sign && lst->prc > cnt + num_q &&
			lst->wdth > lst->prc + sign)
	{
		if (check_fl(lst->flg, g_fl_min))
			newstr = if_fl_min_wdth_m_prc(lst, sign, neg);
		else
		{
			if (!(newstr = (char*)malloc(sizeof(char) * (lst->wdth + 1))))
				return (0);
			if (lst->prc > cnt && check_fl(lst->typ, g_tp_u | g_tp_ua))
			{
				neg = '-';
				lst->prc = lst->prc - cnt;
			}
			if_flg_not_null(newstr, lst, lst->wdth, neg);
		}
	}
	return (newstr);
}

char	*itoa_printf(t_fl_tp *lst)
{
	char	*newstr;
	char	neg;
	int		num_q;
	int		sign;

	newstr = NULL;
	if (check_fl(lst->typ, g_tp_u | g_tp_ua))
	{
		sign = 0;
		neg = 0;
	}
	else
		sign = check_is_sign(lst, &neg);
	num_q = num_qv(lst, ft_cnt_i_d_u_ua_c(lst));
	newstr = if_itoa_printf(lst, num_q, sign, neg);
	if (newstr != NULL)
		return (newstr);
	else
		newstr = if_itoa_printf1(lst, num_q, sign, neg);
	return (newstr);
}
