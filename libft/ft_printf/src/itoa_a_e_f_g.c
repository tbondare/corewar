/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_aaa_eea_ffa_gga.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 20:15:14 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 15:00:23 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*itoa_aaa_eea_ffa_gga(t_fl_tp *lst)
{
	int				cnt;
	char			neg;
	int				num_q;
	char			*arr;
	long double		mem_val;

	arr = NULL;
	num_q = 0;
	mem_val = lst->val.lndbl;
	cnt = cnt_till_aa_ee_ff_gg(10, &mem_val, lst);
	if (check_fl(lst->typ, g_tp_f | g_tp_fa | g_tp_g | g_tp_ga))
		num_q = num_qv(lst, cnt);
	if (lst->prc == 0)
		lst->prc = 6;
	arr = outp_float(lst, cnt + lst->prc + check_is_sign_in_float(lst, &neg)
			+ num_q, cnt, &mem_val);
	return (arr);
}
