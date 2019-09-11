/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:52:13 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/30 15:39:03 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *var;

	var = *alst;
	if (*alst && del)
	{
		while (var)
		{
			*alst = var;
			del(var->content, var->content_size);
			free(*alst);
			*alst = NULL;
			var = var->next;
		}
	}
}
