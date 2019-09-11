/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:26:59 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/30 17:45:48 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *newlist;
	t_list *ft;
	t_list *first;

	if (!(lst))
		return (NULL);
	ft = f(lst);
	if (!(newlist = ft_lstnew(ft->content, ft->content_size)))
		return (NULL);
	first = newlist;
	lst = lst->next;
	while (lst)
	{
		ft = f(lst);
		if (!(newlist->next = ft_lstnew(ft->content, ft->content_size)))
			return (NULL);
		lst = lst->next;
		newlist = newlist->next;
	}
	return (first);
}
