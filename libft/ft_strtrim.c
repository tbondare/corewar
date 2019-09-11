/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 16:30:33 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/24 18:34:38 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*newstr;
	size_t	i;
	size_t	l;
	size_t	g;

	i = 0;
	g = 0;
	if (!s)
		return (NULL);
	l = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == ',' || s[i] == '\n' || s[i] == '\t')
		i++;
	while ((s[l] == ' ' || s[l] == ',' || s[l] == '\n' || s[l] == '\t')
			&& l > i)
		l--;
	if (!(newstr = (char*)malloc(sizeof(char) * (l - i + 1) + 1)))
		return (NULL);
	while (i <= l && s[i])
	{
		newstr[g] = s[i];
		i++;
		g++;
	}
	newstr[g] = '\0';
	return (newstr);
}
