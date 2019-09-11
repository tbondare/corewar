/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcnt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 12:54:32 by tbondare          #+#    #+#             */
/*   Updated: 2017/12/04 14:33:55 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstcnt(t_list *lst)
{
	size_t cnt;

	cnt = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		cnt++;
		lst = lst->next;
	}
	return (cnt);
}
