/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 20:08:14 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/25 22:15:17 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void print_error(char *error)
{
	ft_putendl(error);
	exit(1);
}
int	found_point_cor(char *file_name)
{
	char *point_str;

	point_str = ft_strrchr(file_name, '.');
	if (point_str)
	{
		if (ft_strequ(point_str + 1, "cor"))
			return (1);
	}
	return (0);
}

int	found_same_unic_num(t_carriage *frst, int djt)
{
	t_carriage *crn;

	crn = frst;
	while (crn)
	{
		if (crn->unic_num_plr == djt)
		{
			return 1;
		}
		crn = crn->next;
	}
	return 0;
}

void	found_flg_min_n(char **argv, int *j, t_carriage **frst)
{
	t_carriage *crn;

	if (argv[*j] && ft_atoi_strict(argv[*j]) &&
			ft_atoi(argv[*j]) <= MAX_PLAYERS && ft_atoi(argv[*j]) >= 1)
	{
		if (argv[(*j) + 1] && found_point_cor(argv[++(*j)]) && !found_same_unic_num(*frst,ft_atoi(argv[(*j) - 1])))
		{
			crn = add_player_to_list(frst, argv[*j]);
			crn->unic_num_plr = ft_atoi(argv[(*j) - 1]);
			crn->reg[0] = -crn->unic_num_plr;
			return ;
		}	
	}
	print_error("Invalid champion id for option -n");
}

int		choose_champ_id(t_carriage *champs)
{
	int			id;

	id = 1;
	while (found_same_unic_num(champs, id))
	{
		++id;
	}
	return (id);
}

int	define_next_unic_num(t_carriage *frst, int cnt_plr)
{
	int			i;
	t_carriage	*crn;

	i = 0;
	crn = frst;
	while (crn)
	{
		if (crn->unic_num_plr > cnt_plr) {
			print_error("Invalid player number");
		}
		crn = crn->next;
	}
	crn = frst;
	while (crn)
	{
		if (crn->unic_num_plr == 0) {
			crn->unic_num_plr = choose_champ_id(frst);
		}
		i++;
		crn = crn->next;
	}
	return i;
}

int	read_inp_str(int argc, char **argv, t_vm_data *data)
{
	int j;
	int cnt_plr;

	j = 1;
	cnt_plr = 0;
	while (j < argc && cnt_plr < MAX_PLAYERS)
	{
		if (ft_strequ(argv[j], "-dump"))
		{
			if (j + 1  == argc || !ft_atoi_strict(argv[j + 1]))
				print_error("Invalid champion id for option -dump");
			data->dump_num = ft_atoi(argv[++j]);
		}
		else if (ft_strequ(argv[j], "-n")) 
		{
			j++;
			found_flg_min_n(argv, &j, &data->frst);	
			cnt_plr++;
		}
		else if (found_point_cor(argv[j])) {
			add_player_to_list(&data->frst, argv[j]);
			cnt_plr++;
		}
		else
			print_error("error input");
		j++;
	}
	//ft_putnbr(cnt_plr);exit(1);
	return define_next_unic_num(data->frst, cnt_plr);
}
