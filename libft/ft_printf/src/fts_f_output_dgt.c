/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_f_output_dgt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 18:16:44 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 15:46:02 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	outp_id_j(t_fl_tp *lst, char *newstr, int *mem_w)
{
	int				i;
	struct lconv	*lc;

	lc = localeconv();
	i = 0;
	lst->val.uimx = lst->val.imx < 0 ? -lst->val.imx : lst->val.imx;
	lst->val.imx == 0 ? newstr[*mem_w] = '0' : 0;
	while (lst->val.uimx)
	{
		if (check_fl(lst->flg, g_fl_quo) && i != 0 && i % 3 == 0 &&
				lc->thousands_sep[0] != '\0')
			newstr[(*mem_w)--] = *(lc->thousands_sep);
		newstr[(*mem_w)--] = lst->val.uimx % 10 + '0';
		lst->val.uimx = lst->val.uimx / 10;
		i++;
	}
}

void	outp_uox_xa_j(t_fl_tp *lst, char *newstr, int *mem_w, int base)
{
	int				i;
	struct lconv	*lc;

	lc = localeconv();
	i = 0;
	lst->val.uimx == 0 ? newstr[(*mem_w)--] = '0' : 0;
	while (lst->val.uimx)
	{
		if (check_fl(lst->flg, g_fl_quo) && i != 0 && i % 3 == 0 &&
				lc->thousands_sep[0] != '\0')
			newstr[(*mem_w)--] = *(lc->thousands_sep);
		if (check_fl(lst->typ, g_tp_x) && lst->val.uimx % base > 9)
			newstr[(*mem_w)--] = lst->val.uimx % base + 'a' - 10;
		else if (check_fl(lst->typ, g_tp_xa) && lst->val.uimx % base > 9)
			newstr[(*mem_w)--] = lst->val.uimx % base + 'A' - 10;
		else
			newstr[(*mem_w)--] = lst->val.uimx % base + '0';
		lst->val.uimx = lst->val.uimx / base;
		i++;
	}
}

void	outp_id_da(t_fl_tp *lst, char *newstr, int *mem_w)
{
	int				i;
	struct lconv	*lc;

	lc = localeconv();
	i = 0;
	if (lst->val.ln == 0)
	{
		newstr[*mem_w] = '0';
		(*mem_w)--;
		i++;
	}
	lst->val.uln = lst->val.ln < 0 ? -lst->val.ln : lst->val.ln;
	while (lst->val.uln)
	{
		if (check_fl(lst->flg, g_fl_quo) && i != 0 && i % 3 == 0 &&
				lc->thousands_sep[0] != '\0')
			newstr[(*mem_w)--] = *(lc->thousands_sep);
		newstr[(*mem_w)--] = lst->val.uln % 10 + '0';
		lst->val.uln = lst->val.uln / 10;
		i++;
	}
	if (lst->prc > i)
		while (lst->prc-- > i && *mem_w != 0)
			newstr[(*mem_w)--] = '0';
}

void	outp_c_l(t_fl_tp *lst, char *newstr, int *mem_w)
{
	int				i;
	struct lconv	*lc;

	lc = localeconv();
	i = 0;
	lst->val.win == 0 ? newstr[*mem_w] = '0' : 0;
	lst->val.win = lst->val.win < 0 ? -lst->val.win : lst->val.win;
	while (lst->val.win)
	{
		if (check_fl(lst->flg, g_fl_quo) && i != 0 && i % 3 == 0 &&
				lc->thousands_sep[0] != '\0')
			newstr[(*mem_w)--] = *(lc->thousands_sep);
		newstr[(*mem_w)--] = lst->val.win % 10 + '0';
		lst->val.win = lst->val.win / 10;
		i++;
	}
}

void	outp_uua_ooa_xxa(t_fl_tp *lst, char *newstr, int *mem_w, int base)
{
	int				i;
	struct lconv	*lc;

	i = 0;
	lc = localeconv();
	if (lst->val.uln == 0)
		newstr[(*mem_w)--] = '0';
	while (lst->val.uln)
	{
		if (check_fl(lst->flg, g_fl_quo) && i != 0 && i % 3 == 0 &&
				lc->thousands_sep[0] != '\0')
			newstr[(*mem_w)--] = *(lc->thousands_sep);
		if (check_fl(lst->typ, g_tp_x) && lst->val.uln % base > 9)
			newstr[(*mem_w)--] = lst->val.uln % base + 'a' - 10;
		else if (check_fl(lst->typ, g_tp_xa) && lst->val.uln % base > 9)
			newstr[(*mem_w)--] = lst->val.uln % base + 'A' - 10;
		else
			newstr[(*mem_w)--] = lst->val.uln % base + '0';
		lst->val.uln = lst->val.uln / base;
		i++;
	}
	if (check_fl(lst->typ, g_tp_u | g_tp_ua) && lst->prc > lst->wdth)
		while (*mem_w >= 0)
			newstr[(*mem_w)--] = '0';
}
