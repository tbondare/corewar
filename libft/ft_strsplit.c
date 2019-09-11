/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 18:37:33 by tbondare          #+#    #+#             */
/*   Updated: 2017/12/04 15:32:56 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_createarr(char const *s, char c)
{
	size_t	i;
	size_t	cnt;
	char	**arr;

	i = 0;
	cnt = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1] != '\0') || s[0] != c)
			cnt++;
		i++;
	}
	if (!(arr = (char**)malloc(sizeof(char*) * cnt + 1)))
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}

static char		*ft_createnewstr(char const *s, int i, int cnt)
{
	char	*newstr;

	if (!(newstr = (char*)malloc(sizeof(char) * cnt + 1)))
	{
		free(newstr);
		return (NULL);
	}
	newstr[cnt] = '\0';
	cnt--;
	while (cnt >= 0)
		newstr[cnt--] = s[i--];
	return (newstr);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	ints[3];
	char	**arr;

	ints[0] = 0;
	ints[1] = 0;
	if (!(arr = ft_createarr(s, c)))
		return (NULL);
	while (s[ints[0]])
	{
		s[ints[0]] == c ? ints[0]++ : 0;
		ints[2] = 0;
		while (s[ints[0]] != c && s[ints[0]] != '\0')
		{
			ints[0]++;
			ints[2]++;
		}
		if (ints[2] == 0)
			continue;
		ints[0]--;
		if (!(arr[ints[1]++] = ft_createnewstr(s, ints[0], ints[2])))
			return (NULL);
		ints[0]++;
	}
	arr[ints[1]] = NULL;
	return (arr);
}
