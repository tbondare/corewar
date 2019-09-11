/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 18:08:19 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/30 18:48:25 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cnt(int n)
{
	int				cnt;
	long long int	memn;

	memn = (long long int)n;
	if (n <= 0)
		cnt = 1;
	else
		cnt = 0;
	memn = memn < 0 ? -memn : memn;
	while (memn)
	{
		memn = memn / 10;
		cnt++;
	}
	return (cnt);
}

char		*ft_itoa(int n)
{
	char			*newstr;
	long long int	memn;
	int				cnt;
	char			neg;

	neg = n < 0 ? '-' : 0;
	cnt = ft_cnt(n);
	if (!(newstr = (char*)malloc(sizeof(char) * (cnt + 1))))
		return (NULL);
	newstr[cnt--] = '\0';
	n == 0 ? newstr[cnt] = '0' : 0;
	memn = (long long int)n;
	memn = memn < 0 ? -memn : memn;
	while (memn)
	{
		newstr[cnt--] = memn % 10 + '0';
		memn = memn / 10;
	}
	neg == '-' ? newstr[cnt] = neg : 0;
	return (newstr);
}
