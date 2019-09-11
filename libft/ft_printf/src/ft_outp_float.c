/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outp_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:35:46 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 15:40:00 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*if_op_fl(t_fl_tp *lst, int *num_dgt, int *mem_cnt, int *i)
{
	char *arr;

	arr = (char*)malloc(sizeof(char) * (*num_dgt + 2));
	if (lst->val.lndbl < 0)
	{
		lst->val.lndbl = lst->val.lndbl * -1;
		arr[(*i)++] = '-';
		(*num_dgt)--;
	}
	if (lst->val.lndbl < 1)
	{
		arr[(*i)++] = '0';
		(*mem_cnt)--;
		(*num_dgt)--;
	}
	return (arr);
}

void	if_dgt_more_five(int dgt, char *arr, int i, struct lconv *lc)
{
	if (dgt >= 5)
	{
		arr[(i)--] = '\0';
		while (arr[i] == '9')
		{
			arr[i] = 0 + '0';
			i--;
			if (arr[i] == *(lc->decimal_point))
				i--;
		}
		arr[i] = arr[i] + 1;
	}
	else
		arr[i] = '\0';
}

int		while_if(long double *mem_val, int *mem_cnt, char *arr, int *i)
{
	int				dgt;
	struct lconv	*lc;

	lc = localeconv();
	dgt = *mem_val * 10;
	*mem_val = *mem_val * 10 - dgt;
	if (*mem_cnt > 0)
		(*mem_cnt)--;
	else if (*mem_cnt == 0)
	{
		arr[(*i)++] = *(lc->decimal_point);
		*mem_cnt = -1;
	}
	return (dgt);
}

char	*outp_float(t_fl_tp *lst, int num_dgt, int cnt, long double *mem_val)
{
	int				i;
	int				dgt;
	char			*arr;
	int				mem_cnt;
	struct lconv	*lc;

	lc = localeconv();
	i = 0;
	mem_cnt = cnt;
	arr = if_op_fl(lst, &num_dgt, &mem_cnt, &i);
	while (num_dgt)
	{
		dgt = while_if(mem_val, &mem_cnt, arr, &i);
		arr[(i)++] = dgt + '0';
		num_dgt--;
	}
	dgt = *mem_val * 10;
	if_dgt_more_five(dgt, arr, i, lc);
	if (check_fl(lst->flg, g_fl_quo) && cnt > 3 && lc->thousands_sep[0] != '\0')
		arr = quote(arr, cnt);
	return (arr);
}
