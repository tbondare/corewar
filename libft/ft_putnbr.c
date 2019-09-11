/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 12:17:33 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/30 18:45:52 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				ft_counter(int n)
{
	int					cnt;
	unsigned long int	memn;

	memn = (unsigned long int)n;
	if (n < 0)
		memn = -memn;
	cnt = 0;
	while (memn)
	{
		memn = memn / 10;
		cnt++;
	}
	return (cnt);
}

static long long int	ft_dnm(int cnt)
{
	long long int dnm;

	dnm = 1;
	while (cnt > 1)
	{
		cnt--;
		dnm = dnm * 10;
	}
	return (dnm);
}

void					ft_putnbr(int n)
{
	long long int	memn;
	char			c;
	int				cnt;
	long long int	dnm;

	cnt = ft_counter(n);
	dnm = ft_dnm(cnt);
	if (n < 0)
		ft_putchar('-');
	memn = (long long int)n;
	if (n < 0)
		memn = -memn;
	while (memn)
	{
		c = memn / dnm + '0';
		memn = memn % dnm;
		dnm = dnm / 10;
		ft_putchar(c);
	}
	while (memn == 0 && dnm)
	{
		ft_putchar('0');
		dnm = dnm / 10;
	}
}
