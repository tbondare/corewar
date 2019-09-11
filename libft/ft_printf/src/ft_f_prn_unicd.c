/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_f_prn_unicd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 15:51:11 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 15:32:08 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	uf_in_ucod(int *cnt, wchar_t wc, char *str)
{
	if (0 <= wc && wc <= 0x7f)
		str[0] = (char)wc;
	else if (0x80 <= wc && wc <= 0x7ff)
	{
		str[0] = (0xc0 | (wc >> 6));
		str[1] = (0x80 | (wc & 0x3f));
		*cnt = 2;
	}
	else if (0x800 <= wc && wc <= 0xffff)
	{
		str[0] = (0xe0 | (wc >> 12));
		str[1] = (0x80 | ((wc >> 6) & 0x3f));
		str[2] = (0x80 | (wc & 0x3f));
		*cnt = 3;
	}
	else if (0x10000 <= wc && wc <= 0x1fffff)
	{
		str[0] = (0xf0 | (wc >> 18));
		str[1] = (0x80 | ((wc >> 12) & 0x3f));
		str[2] = (0x80 | ((wc >> 6) & 0x3f));
		str[3] = (0x80 | (wc & 0x3f));
		*cnt = 4;
	}
}

void	bin_op_for_unicode(t_fl_tp *lst, int *cnt, int i, char *str)
{
	wchar_t wc;

	if (check_fl(lst->typ, g_tp_c | g_tp_ca))
	{
		wc = lst->val.win;
		uf_in_ucod(cnt, wc, str);
	}
	else if ((check_fl(lst->typ, g_tp_s | g_tp_sa)))
	{
		wc = ((wchar_t*)lst->val.pnt)[i];
		uf_in_ucod(cnt, wc, str);
	}
}
