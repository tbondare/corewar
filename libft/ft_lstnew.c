/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 12:09:09 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/30 19:07:00 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *newlist;

	if (!(newlist = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		newlist->content = NULL;
		newlist->content_size = 0;
		newlist->next = NULL;
		return (newlist);
	}
	if (!(newlist->content = (void*)malloc(sizeof(void) * content_size)))
		return (NULL);
	newlist->content_size = content_size;
	newlist->next = NULL;
	ft_memcpy(newlist->content, content, sizeof(void) * content_size);
	return (newlist);
}
