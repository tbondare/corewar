/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_for_pr_cca_ssa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 19:15:17 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 15:34:34 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*if_tp_c(t_fl_tp *lst, char *newstr, char sgn, int i)
{
	if (check_fl(lst->flg, g_fl_min) && lst->wdth > 1)
	{
		newstr = (char*)malloc(sizeof(char) * lst->wdth + 1);
		newstr[i++] = lst->val.uln;
		while (--lst->wdth)
			newstr[i++] = sgn;
	}
	else if (lst->wdth > 1)
	{
		newstr = (char*)malloc(sizeof(char) * lst->wdth + 1);
		if (check_fl(lst->flg, g_fl_nll))
			sgn = '0';
		while (--lst->wdth)
			newstr[i++] = sgn;
		newstr[i++] = lst->val.uln;
	}
	else
	{
		newstr = (char*)malloc(sizeof(char) * 2);
		newstr[i++] = lst->val.uln;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*if_wd_m_prc_c(t_fl_tp *lst, char *newstr, char sgn, int *i)
{
	int j;

	j = 0;
	newstr = (char*)malloc(sizeof(char) * lst->wdth + 1);
	if (check_fl(lst->flg, g_fl_nll))
		sgn = '0';
	if (lst->prc < (int)ft_strlen(lst->val.str) && lst->prc > 0 &&
			lst->prc_star != '-')
		lst->wdth = lst->wdth - lst->prc;
	else
		lst->wdth = lst->wdth - ft_strlen(lst->val.str);
	while (lst->wdth--)
		newstr[(*i)++] = sgn;
	if (lst->prc == 0 && lst->prc_star != '-')
		lst->prc = ft_strlen(lst->val.str);
	while (lst->val.str[j] && lst->prc-- > 0)
		newstr[(*i)++] = lst->val.str[j++];
	return (newstr);
}

char	*else_f_pt_s(t_fl_tp *lst, char *newstr, char sgn, int *i)
{
	if ((lst->wdth > (int)ft_strlen(lst->val.str) ||
				lst->wdth > lst->prc) && lst->prc_star != '-')
		newstr = if_wd_m_prc_c(lst, newstr, sgn, i);
	else if (lst->prc == 0 && lst->prc_star == '-' &&
			lst->wdth > (int)ft_strlen(lst->val.str))
	{
		newstr = (char*)malloc(sizeof(char) * lst->wdth + 1);
		if (check_fl(lst->flg, g_fl_nll))
			sgn = '0';
		while (lst->wdth--)
			newstr[(*i)++] = sgn;
	}
	else
	{
		newstr = malloc(sizeof(char) * (int)ft_strlen(lst->val.str) + 1);
		if (lst->prc == 0 && lst->prc_star != '-')
			lst->prc = ft_strlen(lst->val.str);
		while (lst->val.str[(*i)] && lst->prc-- > 0)
		{
			newstr[(*i)] = lst->val.str[(*i)];
			(*i)++;
		}
	}
	return (newstr);
}

char	*if_tp_s_str_n_nul(t_fl_tp *lst, char *newstr, int i, char sgn)
{
	if (check_fl(lst->flg, g_fl_min) &&
			lst->wdth > (int)ft_strlen(lst->val.str))
	{
		newstr = (char*)malloc(sizeof(char) * lst->wdth + 1);
		if (lst->prc == 0 && lst->prc_star != '-')
			lst->prc = ft_strlen(lst->val.str);
		while (lst->val.str[i] && lst->prc-- > 0)
		{
			newstr[i] = lst->val.str[i];
			i++;
			lst->wdth--;
		}
		while (lst->wdth--)
			newstr[i++] = sgn;
	}
	else
		newstr = else_f_pt_s(lst, newstr, sgn, &i);
	newstr[i] = '\0';
	return (newstr);
}

char	*str_null(t_fl_tp *lst, char *newstr, int i, char sgn)
{
	if (lst->prc_star == '-' && lst->wdth > 0)
	{
		if (!(newstr = (char*)malloc(sizeof(char) * lst->wdth + 1)))
			return (0);
		if (check_fl(lst->flg, g_fl_nll))
			sgn = '0';
		while (lst->wdth-- > 0)
			newstr[i++] = sgn;
		newstr[i] = '\0';
	}
	else
		newstr = if_val_null(newstr);
	return (newstr);
}
