/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_determine_flgs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:19:36 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 16:26:21 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*create_dgt_str(const char *frmt, int *i)
{
	char *num;
	char str[2];

	str[1] = '\0';
	num = ft_strnew(0);
	while (frmt[*i] && (frmt[*i] >= '0' && frmt[*i] <= '9'))
	{
		str[0] = frmt[*i];
		num = rejoin(num, str[0]);
		(*i)++;
	}
	return (num);
}

void	determine_dgt_data(const char *frmt, int *i, t_fl_tp *lst)
{
	char *num;

	num = create_dgt_str(frmt, i);
	if (frmt[*i] == '$')
		lst->ind_arg = ft_atoi(num);
	else
	{
		lst->wdth = ft_atoi(num);
		(*i)--;
	}
	free(num);
}

void	determine_precision(const char *frmt, int *i, t_fl_tp *lst)
{
	char *num;

	(*i)++;
	if ((frmt[*i] <= '0' || frmt[*i] > '9') && frmt[*i] != '*')
	{
		lst->prc = 0;
		lst->prc_star = '-';
		if (frmt[*i] != '0')
			(*i)--;
		return ;
	}
	if ((frmt[*i] == '*'))
	{
		lst->prc_star = '*';
		if (frmt[(*i) + 1] < '0' || frmt[(*i) + 1] > '9')
			return ;
		(*i)++;
	}
	num = create_dgt_str(frmt, i);
	lst->prc = ft_atoi(num);
	free(num);
	if (lst->prc_star != '*')
		(*i)--;
}

void	determine_width(const char *frmt, int *i, t_fl_tp *lst)
{
	char *num;

	lst->wdth_star = '*';
	if ((frmt[(*i) + 1] < '0' || frmt[(*i) + 1] > '9'))
		return ;
	(*i)++;
	num = create_dgt_str(frmt, i);
	lst->mem = ft_atoi(num);
	(*i)--;
	free(num);
}

void	determine_md_len(const char *frmt, int *i, t_fl_tp *lst, t_arr *arr)
{
	if (frmt[*i] == 'h' && frmt[(*i) + 1] == 'h')
	{
		(*lst).md_len = set_flg((*lst).md_len, g_ln_hh);
		(*i)++;
	}
	else if (frmt[*i] == 'l' && frmt[(*i) + 1] == 'l')
	{
		(*lst).md_len = set_flg((*lst).md_len, g_ln_ll);
		(*i)++;
	}
	else
		(*lst).md_len = set_flg((*lst).md_len, arr[frmt[*i] -
				g_ar_frst].bit_flg);
}
