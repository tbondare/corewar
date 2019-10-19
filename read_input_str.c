/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 20:08:14 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/16 20:16:36 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

int	found_point_cor(char *file_name)
{
	char *point_str;

	point_str = ft_strchr(file_name, '.');
	if (point_str != NULL)
	{
		if (ft_strequ(point_str + 1, "cor") == 1)
			return (1);
	}
	return (0);
}

int	found_same_unic_num(t_carriage **frst, int djt, int cnt_plr)
{
	t_carriage *crn;

	crn = *frst;
	while (crn)
	{
		if (crn->unic_num_plr == djt)
		{
			crn->unic_num_plr = cnt_plr;
			return (1);
		}
		crn = crn->next;
	}
	return (0);
}

int	found_flg_min_n(char **argv, int *j, t_carriage **frst, int *cnt_plr)
{
	t_carriage *crn;

	if (ft_strequ(argv[*j], "-n") == 1)
	{
		(*j)++;
		if (ft_isdigit(argv[*j][0]) == 1 &&
				ft_atoi(argv[*j]) <= MAX_PLAYERS && ft_atoi(argv[*j]) >= 1)
		{
			if (found_point_cor(argv[++(*j)]) == 1)
			{
				(*cnt_plr)++;
				crn = add_player_to_list(frst, argv[*j]);
				found_same_unic_num(frst, ft_atoi(argv[(*j) - 1]), *cnt_plr);
				crn->unic_num_plr = ft_atoi(argv[(*j) - 1]);
			}
			else
				return (0);
		}
		else
			return (0);
	}
	return (1);
}

int	define_next_unic_num(t_carriage *frst)
{
	int			num;
	t_carriage	*crn;

	num = 1;
	while (num <= MAX_PLAYERS)
	{
		crn = frst;
		while (crn)
		{
			if (crn->unic_num_plr == num)
				break ;
			crn = crn->next;
		}
		if (crn == NULL)
			return (num);
		num++;
	}
	return (num);
}

int	read_inp_str(int argc, char **argv, t_vm_data *data)
{
	int j;
	int cnt_plr;

	j = 1;
	cnt_plr = 0;
	if (ft_strequ(argv[j], "-dump") == 1)
	{
		data->is_dump = 1;
		data->dump_num = ft_atoi(argv[++j]);
		j++;
	}
	while (j < argc && cnt_plr <= MAX_PLAYERS)
	{
		if (found_flg_min_n(argv, &j, &data->frst, &cnt_plr) == 1)
        {
            if (found_point_cor(argv[j]) == 1)
            {
                cnt_plr++;
                add_player_to_list(&data->frst, argv[j]);
            }
        }
		j++;
	}
	return (cnt_plr);
}
