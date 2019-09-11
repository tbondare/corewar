/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cnt_i_d_u_ua_c.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 18:43:53 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 15:26:59 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	cnt_id_da(t_fl_tp *lst, int *cnt)
{
	long long int n;

	if (lst->val.ln == 0)
		*cnt = 1;
	n = lst->val.ln;
	n = n < 0 ? -n : n;
	while (n)
	{
		n = n / 10;
		(*cnt)++;
	}
	return (*cnt);
}

int	cnt_id_j(t_fl_tp *lst, int *cnt)
{
	intmax_t n;

	n = lst->val.imx;
	n = n < 0 ? -n : n;
	while (n)
	{
		n = n / 10;
		(*cnt)++;
	}
	return (*cnt);
}

int	cnt_u_j(t_fl_tp *lst, int *cnt)
{
	uintmax_t n;

	n = lst->val.uimx;
	if (lst->val.uimx == 0)
		*cnt = 1;
	while (n)
	{
		n = n / 10;
		(*cnt)++;
	}
	return (*cnt);
}

int	cnt_u_ua(t_fl_tp *lst, int *cnt)
{
	unsigned long long int n;

	n = lst->val.uln;
	if (lst->val.uln == 0)
	{
		if (lst->prc == 0)
			return (*cnt);
		*cnt = 1;
	}
	while (n)
	{
		n = n / 10;
		(*cnt)++;
	}
	return (*cnt);
}

int	ft_cnt_i_d_u_ua_c(t_fl_tp *lst)
{
	int		cnt;
	wint_t	n;

	cnt = 0;
	if (check_fl(lst->typ, g_tp_i | g_tp_d) && check_fl(lst->md_len, g_ln_j))
		return (cnt_id_j(lst, &cnt));
	else if (check_fl(lst->typ, g_tp_u) && check_fl(lst->md_len, g_ln_j))
		return (cnt_u_j(lst, &cnt));
	else if (check_fl(lst->typ, g_tp_i | g_tp_d | g_tp_da))
		return (cnt_id_da(lst, &cnt));
	else if (check_fl(lst->typ, g_tp_u | g_tp_ua))
		return (cnt_u_ua(lst, &cnt));
	else if (check_fl(lst->typ, g_tp_c) && check_fl(lst->md_len, g_ln_l))
	{
		n = lst->val.win;
		n = n < 0 ? -n : n;
		while (n)
		{
			n = n / 10;
			cnt++;
		}
	}
	return (cnt);
}
