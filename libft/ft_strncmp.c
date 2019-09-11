/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 15:23:38 by tbondare          #+#    #+#             */
/*   Updated: 2017/12/01 16:17:44 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int dif;

	if (n == 0)
		return (0);
	n--;
	while ((unsigned char)*s1 &&
			(unsigned char)*s1 == (unsigned char)*s2 && n--)
	{
		s1++;
		s2++;
	}
	dif = (unsigned char)*s1 - (unsigned char)*s2;
	return (dif);
}
