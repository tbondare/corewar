/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrvrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:56:42 by tbondare          #+#    #+#             */
/*   Updated: 2017/12/04 14:20:30 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrvrs(t_list **lst)
{
	t_list *current;
	t_list *nxt;

	current = (*lst)->next;
	(*lst)->next = NULL;
	while (current)
	{
		nxt = current->next;
		ft_lstadd(&(*lst), current);
		current = nxt;
	}
}
