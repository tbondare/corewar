/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 13:54:43 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 15:59:54 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*if_wd_m_cnt(t_fl_tp *lst, char *allstr, char *str, int mem_cnt)
{
	int i;
	int j;

	i = 0;
	j = 0;
	allstr = (char *)malloc(sizeof(char) * lst->wdth + 1);
	lst->wdth = lst->wdth - mem_cnt;
	if (check_fl(lst->flg, g_fl_nll))
		while (lst->wdth--)
			allstr[i++] = '0';
	else if (check_fl(lst->flg, g_fl_min))
	{
		while (str[j] != '\0')
			allstr[i++] = str[j++];
		while (lst->wdth--)
			allstr[i++] = ' ';
	}
	else
		while (lst->wdth--)
			allstr[i++] = ' ';
	while (str[j] != '\0')
		allstr[i++] = str[j++];
	ft_strdel(&str);
	allstr[i] = '\0';
	return (allstr);
}

int		ft_memory(t_fl_tp *lst, char **str)
{
	int i;

	i = 0;
	if (lst->prc > 0)
	{
		if (!(*str = (char *)malloc(sizeof(char) * lst->prc + 4 + 1)))
			return (0);
	}
	else
	{
		while (((wchar_t *)lst->val.pnt)[i] != '\0')
			i++;
		if (!(*str = (char *)malloc(sizeof(char) * i * 4 + 1)))
			return (0);
	}
	return (0);
}

char	*ft_else_tp_s(t_fl_tp *lst, char *str, int cnt, int *mem_cnt)
{
	int i;
	int j;

	i = 0;
	j = 0;
	ft_memory(lst, &str);
	while (((wchar_t *)lst->val.pnt)[i] != '\0')
	{
		cnt = 1;
		bin_op_for_unicode(lst, &cnt, i, &str[j]);
		*mem_cnt = cnt + *mem_cnt;
		j = j + cnt;
		if (lst->prc < *mem_cnt && lst->prc > 0)
		{
			*mem_cnt = *mem_cnt - cnt;
			break ;
		}
		i++;
	}
	return (str);
}

char	*ft_else_if_pr_un(t_fl_tp *lst, char *str, int cnt)
{
	char	*allstr;
	int		mem_cnt;

	mem_cnt = 0;
	allstr = NULL;
	if ((wchar_t *)lst->val.pnt == NULL)
		return (if_val_null(str));
	if (lst->prc == 0 && lst->prc_star == '-')
	{
		str = (char *)malloc(sizeof(char));
		mem_cnt = 0;
	}
	else
		str = ft_else_tp_s(lst, str, cnt, &mem_cnt);
	str[mem_cnt] = '\0';
	if (lst->wdth > mem_cnt)
		return (if_wd_m_cnt(lst, allstr, str, mem_cnt));
	return (str);
}

char	*print_unicode(t_fl_tp *lst)
{
	char	*str;
	int		cnt;
	int		i;

	i = 0;
	cnt = 1;
	str = NULL;
	if ((check_fl(lst->typ, g_tp_c) && (check_fl(lst->md_len, g_ln_l))) ||
			(check_fl(lst->typ, g_tp_ca)))
	{
		str = (char *)malloc(sizeof(char) * 4 + 1);
		bin_op_for_unicode(lst, &cnt, i, str);
		str[cnt] = '\0';
	}
	else if ((check_fl(lst->typ, g_tp_s) && (check_fl(lst->md_len, g_ln_l))) ||
			(check_fl(lst->typ, g_tp_sa)))
		str = ft_else_if_pr_un(lst, str, cnt);
	return (str);
}
