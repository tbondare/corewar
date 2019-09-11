/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cnt_o_x_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:10:45 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 15:05:04 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		cnt_ox_xa_j(t_fl_tp *lst, int *cnt, int base)
{
	uintmax_t n;

	n = lst->val.uimx;
	while (n)
	{
		n = n / base;
		(*cnt)++;
	}
	return (*cnt);
}

int		cnt_ox_xa(t_fl_tp *lst, int *cnt, int base)
{
	unsigned long long int n;

	n = lst->val.uln;
	if (lst->val.uln == 0)
		*cnt = 1;
	else if (check_fl(lst->flg, g_fl_grl) &&
			!(check_fl(lst->typ, g_tp_x | g_tp_xa)))
		*cnt = 1;
	else if (check_fl(lst->flg, g_fl_grl) && lst->val.uln != 0 &&
			check_fl(lst->typ, g_tp_x | g_tp_xa))
		*cnt = 2;
	while (n)
	{
		n = n / base;
		(*cnt)++;
	}
	return (*cnt);
}

int		cnt_p(t_fl_tp *lst, int *cnt, int base)
{
	unsigned long long int n;

	n = (unsigned long long int)lst->val.pnt;
	if (lst->val.pnt == 0 && lst->prc == -1)
		*cnt = 3;
	else
	{
		while (n)
		{
			n = n / base;
			(*cnt)++;
		}
		*cnt = *cnt + 2;
	}
	return (*cnt);
}

int		ft_cnt_oo_xx_b(t_fl_tp *lst, int base)
{
	int	cnt;

	cnt = 0;
	if (check_fl(lst->typ, g_tp_o | g_tp_x | g_tp_xa) &&
			check_fl(lst->md_len, g_ln_j))
		return (cnt_ox_xa_j(lst, &cnt, base));
	else if (check_fl(lst->typ, g_tp_p))
		return (cnt_p(lst, &cnt, base));
	else
		return (cnt_ox_xa(lst, &cnt, base));
}

void	outp_p(t_fl_tp *lst, char *newstr, int *mem_w, int base)
{
	unsigned long long int dir;

	dir = (unsigned long long int)lst->val.pnt;
	if (lst->val.pnt == 0)
		newstr[(*mem_w)--] = '0';
	while (dir)
	{
		if (dir % 16 > 9)
			newstr[(*mem_w)--] = dir % base + 'a' - 10;
		else
			newstr[(*mem_w)--] = dir % base + '0';
		dir = dir / base;
	}
	if (lst->prc > lst->wdth)
		while (*mem_w >= 2)
			newstr[(*mem_w)--] = '0';
	newstr[(*mem_w)--] = 'x';
	newstr[(*mem_w)--] = '0';
}
