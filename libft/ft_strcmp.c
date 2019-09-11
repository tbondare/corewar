/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 19:15:42 by tbondare          #+#    #+#             */
/*   Updated: 2017/12/04 15:21:40 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int		res;
	size_t	i;

	res = 0;
	i = 0;
	while ((unsigned char)str1[i] != '\0')
	{
		if ((unsigned char)str1[i] != (unsigned char)str2[i])
			break ;
		i++;
	}
	res = (unsigned char)str1[i] - (unsigned char)str2[i];
	return (res);
}
