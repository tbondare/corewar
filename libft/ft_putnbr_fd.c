/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 18:23:32 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/30 12:40:01 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			arr[11];
	long long int	memn;
	char			c;
	int				i;

	i = 0;
	memn = (long long int)n;
	memn = n < 0 ? -memn : memn;
	if (n == 0)
		ft_putchar_fd('0', fd);
	while (memn)
	{
		c = memn % 10;
		memn = memn / 10;
		arr[i] = c + '0';
		i++;
	}
	if (n < 0)
		ft_putchar_fd('-', fd);
	i--;
	while (i >= 0)
	{
		ft_putchar_fd(arr[i], fd);
		i--;
	}
}
