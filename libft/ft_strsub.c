/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 14:59:29 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/24 15:39:12 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (!(newstr = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (len--)
	{
		newstr[i] = s[start];
		i++;
		start++;
	}
	newstr[i] = '\0';
	return (newstr);
}
