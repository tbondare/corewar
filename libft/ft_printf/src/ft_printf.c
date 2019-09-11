/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:02:42 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 15:57:54 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	print_str(char *str)
{
	write(1, str, ft_strlen(str));
	ft_strdel(&str);
}

int		printing_args(t_fl_tp *prm, int *total_strlen)
{
	char	*str;
	t_fl_tp	*lst;
	int		mem_w;

	lst = prm;
	while (lst)
	{
		mem_w = lst->wdth;
		if (check_fl(lst->typ, g_tp_err))
			lst->typ = set_flg(0, g_tp_c);
		if ((if_print_args(lst, &str) != 0 ||
					if_print_args2(lst, &str, total_strlen) ||
					if_print_args3(lst, &str, &mem_w)) && str != 0)
		{
			*total_strlen = *total_strlen + ft_strlen(str);
			print_str(str);
			lst = lst->next;
			continue ;
		}
		if (if_str_nul(&lst, &str, total_strlen, &mem_w) == 0)
			continue ;
		lst = lst->next;
	}
	return (*total_strlen);
}

int		ft_printf(const char *format, ...)
{
	va_list	args;
	t_fl_tp	*prm;
	int		total_strlen;
	t_fl_tp	*mem_var;

	prm = NULL;
	total_strlen = 0;
	va_start(args, format);
	if (fill_struct(&prm, format) == 0)
		return (0);
	determine_args(prm, args);
	printing_args(prm, &total_strlen);
	while (prm)
	{
		ft_strdel(&(prm->str_out));
		mem_var = prm->next;
		free(prm);
		prm = mem_var;
	}
	return (total_strlen);
}
