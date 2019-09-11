/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fns_for_ddgt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:49:20 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 15:20:51 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		check_sign_dif_tp(t_fl_tp *lst)
{
	if (check_fl(lst->typ, g_tp_i | g_tp_d) && check_fl(lst->md_len, g_ln_j))
		return (lst->val.imx < 0);
	else if (check_fl(lst->typ, g_tp_u) && check_fl(lst->md_len, g_ln_j))
		return (0);
	else if (check_fl(lst->typ, g_tp_i | g_tp_d | g_tp_da))
		return (lst->val.ln < 0);
	else if (check_fl(lst->typ, g_tp_u | g_tp_ua))
		return (0);
	else if (check_fl(lst->typ, g_tp_c) && check_fl(lst->md_len, g_ln_l))
		return (lst->val.win < 0);
	return (0);
}

int		check_is_sign(t_fl_tp *lst, char *neg)
{
	int sign;

	sign = 0;
	if (check_fl(lst->flg, g_fl_pls))
	{
		*neg = check_sign_dif_tp(lst) ? '-' : '+';
		sign = 1;
	}
	else if (check_fl(lst->flg, g_fl_spc))
	{
		*neg = check_sign_dif_tp(lst) ? '-' : ' ';
		sign = 1;
	}
	else if (check_sign_dif_tp(lst))
	{
		*neg = '-';
		sign = 1;
	}
	else
		*neg = 0;
	return (sign);
}

int		num_qv(t_fl_tp *lst, int cnt)
{
	int				num_q;
	struct lconv	*lc;

	lc = localeconv();
	num_q = 0;
	if (lc->thousands_sep[0] == '\0')
		return (num_q);
	if (check_fl(lst->flg, g_fl_quo))
	{
		if (cnt > 3)
		{
			if (cnt % 3 == 0)
				num_q = cnt / 3 - 1;
			else
				num_q = cnt / 3;
		}
	}
	return (num_q);
}

void	output_dgt(t_fl_tp *lst, char *newstr, int *mem_w, int base)
{
	if (check_fl(lst->typ, g_tp_i | g_tp_d) && check_fl(lst->md_len, g_ln_j))
		outp_id_j(lst, newstr, mem_w);
	else if (check_fl(lst->typ, g_tp_u | g_tp_o | g_tp_x | g_tp_xa | g_tp_p) &&
			check_fl(lst->md_len, g_ln_j))
		outp_uox_xa_j(lst, newstr, mem_w, base);
	else if (check_fl(lst->typ, g_tp_i | g_tp_d | g_tp_da))
		outp_id_da(lst, newstr, mem_w);
	else if (check_fl(lst->typ, g_tp_u | g_tp_ua | g_tp_o | g_tp_oa
								| g_tp_x | g_tp_xa))
		outp_uua_ooa_xxa(lst, newstr, mem_w, base);
	else if (check_fl(lst->typ, g_tp_c) && check_fl(lst->md_len, g_ln_l))
		outp_c_l(lst, newstr, mem_w);
	else if (check_fl(lst->typ, g_tp_p))
		outp_p(lst, newstr, mem_w, base);
}
