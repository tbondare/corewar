/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_strict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:37:12 by vgrynish          #+#    #+#             */
/*   Updated: 2019/10/25 21:40:41 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

int		ft_atoi_strict(char const *str)
{
	int		abs;

	if (*str == '-' || *str == '+')
		++str;
	if (*str == '\0')
		return (0);
	abs = 0;
	while ('0' <= *str && *str <= '9')
	{
		abs = abs * 10 + (int)(*(str++) - '0');
		if (abs < 0 && !(abs == -2147483648 && *str == '\0'))
			return (0);
	}
	if (*str)
		return (0);
	return (1);
}