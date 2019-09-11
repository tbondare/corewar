/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_flgs_o_x_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:13:32 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 15:48:50 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	if_fl_minus_ooxxb(char *newstr, t_fl_tp *lst, int cnt, int base)
{
	int					res;
	int					mem_w;
	unsigned long long	mem_val;

	mem_w = lst->wdth;
	mem_val = lst->val.uln;
	newstr[mem_w--] = '\0';
	res = lst->wdth - cnt;
	while (res)
	{
		newstr[mem_w--] = ' ';
		res--;
	}
	output_dgt(lst, newstr, &mem_w, base);
	if (check_fl(lst->flg, g_fl_grl) && mem_val != 0)
	{
		if (check_fl(lst->typ, g_tp_xa))
			newstr[mem_w--] = 'X';
		else if (check_fl(lst->typ, g_tp_x))
			newstr[mem_w--] = 'x';
		newstr[mem_w--] = '0';
	}
}

void	if_fl_grill(t_fl_tp *lst, char *newstr, int *mem_w)
{
	if (check_fl(lst->typ, g_tp_xa))
		newstr[(*mem_w)--] = 'X';
	else
		newstr[(*mem_w)--] = 'x';
	newstr[(*mem_w)--] = '0';
}

void	if_flg_null_ooxxb(char *newstr, t_fl_tp *lst, int cnt, int base)
{
	int					mem_w;
	int					res;
	unsigned long long	mem_val;

	mem_w = lst->wdth;
	mem_val = lst->val.uln;
	newstr[mem_w--] = '\0';
	if (check_fl(lst->typ, g_tp_p) && lst->val.pnt == 0)
	{
		lst->wdth = lst->wdth - cnt;
		while (lst->wdth-- > 0)
			newstr[mem_w--] = '0';
		output_dgt(lst, newstr, &mem_w, base);
	}
	else
	{
		output_dgt(lst, newstr, &mem_w, base);
		res = lst->wdth - cnt;
		while (res--)
			newstr[mem_w--] = '0';
		if (check_fl(lst->flg, g_fl_grl) && mem_val != 0)
			if_fl_grill(lst, newstr, &mem_w);
	}
}

void	if_flg_not_null_oxb(char *newstr, t_fl_tp *lst, int base)
{
	int					mem_w;
	unsigned long long	mem_val;

	mem_w = lst->wdth;
	mem_val = lst->val.uln;
	newstr[mem_w--] = '\0';
	if (lst->prc != 0 || (check_fl(lst->typ, g_tp_p) && lst->prc != 0))
		output_dgt(lst, newstr, &mem_w, base);
	else if (check_fl(lst->typ, g_tp_p) && lst->prc == 0)
	{
		newstr[mem_w--] = 'x';
		newstr[mem_w--] = '0';
	}
	if (check_fl(lst->flg, g_fl_grl) && mem_val != 0)
	{
		if (check_fl(lst->typ, g_tp_xa))
			newstr[mem_w--] = 'X';
		else if (check_fl(lst->typ, g_tp_x))
			newstr[mem_w--] = 'x';
		newstr[mem_w--] = '0';
	}
	while (mem_w >= 0)
		newstr[mem_w--] = ' ';
}

char	*if_val_null(char *newstr)
{
	newstr = (char*)malloc(sizeof(char) * 7);
	newstr[0] = '(';
	newstr[1] = 'n';
	newstr[2] = 'u';
	newstr[3] = 'l';
	newstr[4] = 'l';
	newstr[5] = ')';
	newstr[6] = '\0';
	return (newstr);
}
