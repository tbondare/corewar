/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_printf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:04:36 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/03 14:02:58 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

unsigned int	set_flg(unsigned int flags, unsigned int flg)
{
	flags = flags | flg;
	return (flags);
}

int				check_fl(unsigned int flags, unsigned int flg)
{
	if ((flags & flg) != 0)
		return (1);
	return (0);
}

t_fl_tp			*lstnew(void)
{
	t_fl_tp *newlist;

	if (!(newlist = (t_fl_tp*)malloc(sizeof(t_fl_tp))))
		return (NULL);
	newlist->str_out = ft_strnew(0);
	newlist->ind_arg = 0;
	newlist->flg = 0;
	newlist->wdth = 0;
	newlist->prc = -1;
	newlist->md_len = 0;
	newlist->typ = 0;
	newlist->wdth_star = 0;
	newlist->prc_star = 0;
	newlist->ind_arg_wdth = 0;
	newlist->ind_arg_prc = 0;
	newlist->val.ln = 0;
	newlist->val.uln = 0;
	newlist->mem = 0;
	newlist->next = NULL;
	return (newlist);
}

char			*ft_strchar(char const *s1, char const c)
{
	char	*newstr;
	size_t	len;
	size_t	i;

	i = 0;
	if (!(s1))
		return (NULL);
	len = ft_strlen(s1) + 1;
	if (!(newstr = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (*s1)
	{
		newstr[i] = (char)*s1;
		i++;
		s1++;
	}
	newstr[i++] = c;
	newstr[i] = '\0';
	return (newstr);
}

char			*rejoin(char *s1, const char c)
{
	char *tmp;

	tmp = ft_strchar(s1, c);
	ft_strdel(&s1);
	return (tmp);
}
