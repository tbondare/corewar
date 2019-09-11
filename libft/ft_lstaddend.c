/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:07:25 by tbondare          #+#    #+#             */
/*   Updated: 2017/12/04 14:44:52 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **lsta, t_list *new)
{
	t_list *begin;

	begin = *lsta;
	while ((*lsta)->next)
		*lsta = (*lsta)->next;
	(*lsta)->next = new;
	*lsta = begin;
}
