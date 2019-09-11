/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fns_for_fl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:15:46 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 15:25:26 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		check_is_sign_in_float(t_fl_tp *lst, char *neg)
{
	int sign;

	sign = 0;
	if (check_fl(lst->flg, g_fl_pls))
	{
		*neg = lst->val.lndbl < 0 ? '-' : '+';
		sign = 1;
	}
	else if (check_fl(lst->flg, g_fl_spc))
	{
		*neg = lst->val.lndbl < 0 ? '-' : ' ';
		sign = 1;
	}
	else if (lst->val.lndbl < 0)
	{
		*neg = '-';
		sign = 1;
	}
	else
		*neg = 0;
	return (sign);
}

int		cnt_till_aa_ee_ff_gg(int base, long double *mem_val, t_fl_tp *lst)
{
	int cnt;

	cnt = 0;
	*mem_val = *mem_val < 0 ? -*mem_val : *mem_val;
	if (*mem_val >= 1)
	{
		while (*mem_val >= 1)
		{
			*mem_val = *mem_val / base;
			cnt++;
		}
	}
	else
	{
		while (*mem_val < 1)
		{
			*mem_val = *mem_val * base;
			cnt++;
		}
		*mem_val = lst->val.lndbl;
		if (check_fl(*mem_val, g_tp_e | g_tp_ea | g_tp_g | g_tp_ga))
			cnt = -cnt;
	}
	return (cnt);
}

char	*if_quote(char *arr, int *cnt, int *i, int *j)
{
	char *str;

	if ((*cnt) % 3 == 0)
		*cnt = (*cnt) / 3 - 1;
	else if ((*cnt) % 3 != 0)
		*cnt = (*cnt) / 3;
	while (arr[(*i)] != '\0')
		(*i)++;
	*j = *i + *cnt;
	str = (char *)malloc(sizeof(char) * *j + 1);
	return (str);
}

char	*quote(char *arr, int cnt)
{
	char			*str;
	int				i;
	int				j;
	int				multiple;
	struct lconv	*lc;

	lc = localeconv();
	i = 0;
	str = if_quote(arr, &cnt, &i, &j);
	while (arr[i] != *(lc->decimal_point))
		str[j--] = arr[i--];
	str[j--] = arr[i--];
	while (cnt > 0)
	{
		multiple = 3;
		while (multiple--)
			str[j--] = arr[i--];
		str[j--] = *(lc->thousands_sep);
		cnt--;
	}
	str[j] = arr[i];
	ft_strdel(&arr);
	return (str);
}
