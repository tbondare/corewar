/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_players_to_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 20:19:08 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/25 22:15:16 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void			add_player_to_list_crn(t_carriage **crn, char *argv)
{
	int reg_number;

	reg_number = REG_NUMBER;
	while ((*crn)->next)
		(*crn) = (*crn)->next;
	(*crn)->next = (t_carriage *)malloc(sizeof(t_carriage));
	ft_bzero((*crn)->next->reg, reg_number * sizeof(int));
	(*crn)->next->is_killed = 0;
	(*crn)->next->unic_num_plr = 0;
	(*crn)->next->file_name = argv;
	(*crn)->next->command.num_cycle = -1;
	(*crn)->next->cycles_to_die = CYCLE_TO_DIE;
	(*crn)->next->num_checks = 0;
	(*crn)->next->cnt_ccls_to_die = 0;
	(*crn)->next->command.is_arg_type = 1;
	(*crn)->next->num_oper_live = 0;
	(*crn)->next->num_cycle_end_alive = -1;
	(*crn)->next->carry = -1;
	(*crn)->next->reg[0] = -(*crn)->next->unic_num_plr;
	(*crn)->next->next = NULL;
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
		(*frst)->unic_num_plr = 0;
		(*frst)->file_name = argv;
		(*frst)->command.num_cycle = -1;
		(*frst)->cycles_to_die = CYCLE_TO_DIE;
		(*frst)->num_checks = 0;
		(*frst)->cnt_ccls_to_die = 0;
		(*frst)->command.is_arg_type = 1;
		(*frst)->num_oper_live = 0;
		(*frst)->num_cycle_end_alive = -1;
		(*frst)->carry = -1;
		//(*frst)->unic_num_plr = define_next_unic_num(*frst);
		(*frst)->reg[0] = -(*frst)->unic_num_plr;
		(*frst)->next = NULL;
		return (*frst);
	}
	else
		add_player_to_list_crn(&crn, argv);
	return (crn->next);
}
