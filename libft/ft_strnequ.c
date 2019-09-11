/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 13:49:35 by tbondare          #+#    #+#             */
/*   Updated: 2017/12/04 15:27:25 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t i;

	i = 0;
	if (s1 && s2)
	{
		while (((unsigned char)s1[i] == (unsigned char)s2[i]) &&
				(unsigned char)s1[i] && (unsigned char)s2[i] && n--)
			i++;
		if (((unsigned char)s1[i] == (unsigned char)s2[i]) ||
				(!(unsigned char)s1[i] && !(unsigned char)s2[i]) || !n)
			return (1);
	}
	return (0);
}
