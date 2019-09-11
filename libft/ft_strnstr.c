/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 21:02:29 by tbondare          #+#    #+#             */
/*   Updated: 2017/12/01 18:47:14 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t len)
{
	if (*lit == '\0')
		return ((char*)big);
	while (*big && *lit && len)
	{
		if (!ft_strncmp(big, lit, ft_strlen(lit)) && len >= ft_strlen(lit))
			return ((char*)big);
		big++;
		len--;
	}
	return (NULL);
}
