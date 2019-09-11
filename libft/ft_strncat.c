/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 13:14:09 by tbondare          #+#    #+#             */
/*   Updated: 2017/12/04 15:25:51 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	size_t i;
	size_t g;

	i = 0;
	g = 0;
	while (dst[i])
		i++;
	while (src[g] && n--)
		dst[i++] = src[g++];
	dst[i] = '\0';
	return (dst);
}
