/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cca_ssa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:12:55 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 15:59:24 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*print_cca_ssa(t_fl_tp *lst)
{
	int		i;
	char	sgn;
	char	*newstr;

	i = 0;
	sgn = ' ';
	newstr = NULL;
	if (check_fl(lst->typ, g_tp_c))
		newstr = if_tp_c(lst, newstr, sgn, i);
	else if (lst->val.str == NULL)
		newstr = str_null(lst, newstr, i, sgn);
	else if (check_fl(lst->typ, g_tp_s) && lst->val.str != 0)
		newstr = if_tp_s_str_n_nul(lst, newstr, i, sgn);
	return (newstr);
}
