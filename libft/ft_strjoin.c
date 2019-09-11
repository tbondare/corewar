/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 15:43:15 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/24 16:29:08 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(newstr = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (*s1)
	{
		newstr[i] = (char)*s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		newstr[i] = (char)*s2;
		i++;
		s2++;
	}
	newstr[i] = '\0';
	return (newstr);
}
