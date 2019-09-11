/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_printf_ooa_xxa_b.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:08:48 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 15:58:40 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*if_prc_m_wd(t_fl_tp *lst, int base, char *newstr)
{
	int mem_w;

	if (check_fl(lst->typ, g_tp_o | g_tp_oa | g_tp_x | g_tp_xa) &&
		!(check_fl(lst->flg, g_fl_grl)))
		mem_w = lst->prc;
	else if (check_fl(lst->typ, g_tp_o | g_tp_oa))
		mem_w = lst->prc;
	else
		mem_w = lst->prc + 2;
	if (!(newstr = (char*)malloc(sizeof(char) * (mem_w + 1))))
		return (0);
	newstr[mem_w--] = '\0';
	output_dgt(lst, newstr, &mem_w, base);
	if (check_fl(lst->flg, g_fl_grl) && check_fl(lst->typ, g_tp_x | g_tp_xa))
	{
		while (mem_w > 1)
			newstr[(mem_w)--] = '0';
		newstr[(mem_w)--] = 'x';
		newstr[(mem_w)--] = '0';
	}
	else
		while (mem_w >= 0)
			newstr[mem_w--] = '0';
	return (newstr);
}

void	if_lg_min(t_fl_tp *lst, char *newstr, int base, int cnt)
{
	int mem_w;
	int res;

	res = 0;
	mem_w = lst->wdth;
	newstr[mem_w--] = '\0';
	if (check_fl(lst->flg, g_fl_min))
	{
		res = lst->wdth - lst->prc;
		while (res--)
			newstr[mem_w--] = ' ';
		output_dgt(lst, newstr, &mem_w, base);
		res = lst->prc - cnt;
		while (res--)
			newstr[mem_w--] = '0';
	}
	else
	{
		cnt = lst->prc - cnt;
		output_dgt(lst, newstr, &mem_w, base);
		while (cnt--)
			newstr[mem_w--] = '0';
		while (mem_w >= 0)
			newstr[mem_w--] = ' ';
	}
}

char	*if_f_prc_nul(t_fl_tp *lst, char *newstr, int cnt, int base)
{
	if (check_fl(lst->flg, g_fl_grl) && check_fl(lst->typ, g_tp_o | g_tp_oa) &&
		lst->val.uln == 0)
	{
		if (!(newstr = (char*)malloc(sizeof(char) * 2)))
			return (0);
		newstr[0] = '0';
		newstr[1] = '\0';
	}
	else if (check_fl(lst->typ, g_tp_o | g_tp_oa) && lst->val.uln != 0)
	{
		if (!(newstr = (char*)malloc(sizeof(char) * cnt + 1)))
			return (0);
		newstr[cnt--] = '\0';
		output_dgt(lst, newstr, &cnt, base);
		if (check_fl(lst->flg, g_fl_grl))
			newstr[cnt] = '0';
	}
	else
	{
		if (!(newstr = (char*)malloc(sizeof(char) * 1)))
			return (0);
		newstr[0] = '\0';
	}
	return (newstr);
}

char	*itoa_o_x_b(t_fl_tp *lst, int *base, int *cnt, char *newstr)
{
	if (check_fl(lst->typ, g_tp_o | g_tp_oa))
		*base = 8;
	else if (check_fl(lst->typ, g_tp_x | g_tp_xa | g_tp_p))
		*base = 16;
	else if (check_fl(lst->typ, g_tp_b))
		*base = 2;
	*cnt = ft_cnt_oo_xx_b(lst, *base);
	if (lst->prc == 0 && lst->wdth == 0 && (!check_fl(lst->typ, g_tp_p)))
		newstr = if_f_prc_nul(lst, newstr, *cnt, *base);
	else if (lst->wdth > *cnt && lst->prc <= *cnt && lst->wdth > lst->prc)
	{
		if (!(newstr = (char*)malloc(sizeof(char) * (lst->wdth + 1))))
			return (0);
		if (check_fl(lst->flg, g_fl_min))
			if_fl_minus_ooxxb(newstr, lst, *cnt, *base);
		else
		{
			if (check_fl(lst->flg, g_fl_nll))
				if_flg_null_ooxxb(newstr, lst, *cnt, *base);
			else
				if_flg_not_null_oxb(newstr, lst, *base);
		}
	}
	return (newstr);
}

char	*itoa_printf_ooa_xxa_b(t_fl_tp *lst)
{
	char	*newstr;
	int		cnt;
	int		base;

	newstr = NULL;
	base = 0;
	newstr = itoa_o_x_b(lst, &base, &cnt, newstr);
	if (newstr != NULL)
		return (newstr);
	else if (lst->wdth <= cnt && lst->prc <= cnt)
	{
		if (!(newstr = (char*)malloc(sizeof(char) * (cnt + 1))))
			return (0);
		lst->wdth = cnt;
		if_flg_not_null_oxb(newstr, lst, base);
	}
	else if (lst->wdth > cnt && lst->prc > cnt && lst->wdth > lst->prc)
	{
		if (!(newstr = (char*)malloc(sizeof(char) * (lst->wdth + 1))))
			return (0);
		if_lg_min(lst, newstr, base, cnt);
	}
	else if (lst->prc > lst->wdth)
		newstr = if_prc_m_wd(lst, base, newstr);
	return (newstr);
}
