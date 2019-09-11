/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 16:12:50 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/23 19:29:37 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *buf;

	buf = NULL;
	if (size > 9223372036854775807)
		return (NULL);
	buf = (char*)malloc(size);
	if (buf == NULL)
		return (NULL);
	ft_bzero(buf, size);
	return ((char*)buf);
}
