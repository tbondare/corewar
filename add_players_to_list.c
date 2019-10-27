/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_players_to_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 20:19:08 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/22 15:45:43 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void			add_player_to_list_crn(t_carriage **crn, char *argv,
		t_carriage *frst)
{
	int reg_number;

	reg_number = REG_NUMBER;
	while ((*crn)->next)
		(*crn) = (*crn)->next;
	(*crn)->next = (t_carriage *)malloc(sizeof(t_carriage));
	ft_bzero((*crn)->next->reg, reg_number * sizeof(int));
	(*crn)->next->is_killed = 0;
	(*crn)->next->file_name = argv;
	(*crn)->next->command.num_cycle = -1;
	(*crn)->next->cycles_to_die = CYCLE_TO_DIE;
	(*crn)->next->num_checks = 0;
	(*crn)->next->command.is_arg_type = 1;
	(*crn)->next->last_op_live_cycle = -CYCLE_TO_DIE;
	(*crn)->next->carry = -1;
	(*crn)->next->next = NULL;
	(*crn)->next->unic_num_plr = 0; // this is needed for define_next_unic_num()
	(*crn)->next->unic_num_plr = define_next_unic_num(frst);
	(*crn)->next->unic_num_carr = (*crn)->next->unic_num_plr;
	(*crn)->next->reg[0] = -(*crn)->next->unic_num_plr;
}

t_carriage		*add_player_to_list(t_carriage **frst, char *argv)
{
	t_carriage *crn;

	crn = *frst;
	if (*frst == NULL)
	{
		(*frst) = (t_carriage *)malloc(sizeof(t_carriage));
		ft_bzero((*frst)->reg, REG_NUMBER * sizeof(int));
		(*frst)->is_killed = 0;
		(*frst)->file_name = argv;
		(*frst)->command.num_cycle = -1;
		(*frst)->cycles_to_die = CYCLE_TO_DIE;
		(*frst)->num_checks = 0;
		(*frst)->command.is_arg_type = 1;
		(*frst)->last_op_live_cycle = -CYCLE_TO_DIE;
		(*frst)->carry = -1;
		(*frst)->next = NULL;
		(*frst)->unic_num_plr = 0; // this is needed for define_next_unic_num()
		(*frst)->unic_num_plr = define_next_unic_num(*frst);
		(*frst)->unic_num_carr = (*frst)->unic_num_plr;
		(*frst)->reg[0] = -(*frst)->unic_num_plr;
		return (*frst);
	}
	else
		add_player_to_list_crn(&crn, argv, *frst);
	return (crn->next);
}
