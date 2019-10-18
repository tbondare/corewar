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
		*j++;
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

int	define_next_unic_num(t_carriage *frst, int num_chemp)
{
	int			num;
	t_carriage	*crn;
	t_carriage  *crn_frst;

    num = 1;
	if (frst->next == NULL)
        return (num);
	while (num <= MAX_PLAYERS && num_chemp > 1)
	{
        crn = frst;
		while (crn)
		{
			if (crn->unic_num_plr == num && num_chemp > 0)
            {
			    num++;
			    num_chemp--;
                continue ;
            }
			crn = crn->next;
		}
	}
	return (num);
}

int	read_inp_str(int argc, char **argv, t_carriage **frst)
{
	int j;
	int cnt_plr;
	t_carriage *crn;

	j = 1;
	cnt_plr = 0;
	while (j < argc && cnt_plr <= MAX_PLAYERS)
	{
		if (found_flg_min_n(argv, &j, frst, &cnt_plr) != 1)
		{
			if (found_point_cor(argv[j]) == 1)
			{
				cnt_plr++;
				add_player_to_list(frst, argv[j]);
				(*frst)->unic_num_plr = define_next_unic_num(*frst, argc - 1);
			}
		}
		else
        {
            if (found_point_cor(argv[j]) == 1)
            {
                cnt_plr++;
                add_player_to_list(frst, argv[j]);
                crn = *frst;
                while (crn->next)
                    crn = crn->next;
                crn->unic_num_plr = define_next_unic_num(*frst, argc - 1);
            }
        }
		j++;
	}
	return (cnt_plr);
}
