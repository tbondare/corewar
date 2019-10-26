/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_for_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:25:51 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/22 17:52:09 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

int cnt_players(t_carriage *frst)
{
    t_carriage *crn;
    int num;

    num = 0;
    crn = frst;
    while (crn)
    {
        num++;
        crn = crn->next;
    }
    return (num);
}

void	write_introduction(t_carriage *frst)
{
	t_carriage *crn;
	int i;
	int num_pl;

	i = 1;
	num_pl = cnt_players(frst);
	ft_putstr("Introducing contestants...\n");
	while (i <= num_pl)
	{
        crn = frst;
	    while (crn->unic_num_plr != i)
	        crn = crn->next;
		ft_putstr("* Player ");
		ft_putnbr(crn->unic_num_plr);
		ft_putstr(", weighing ");
		ft_putnbr(crn->header.prog_size);
		ft_putstr(" bytes, \"");
		ft_putstr(crn->header.prog_name);
		ft_putstr("\" (\"");
		ft_putstr(crn->header.comment);
		ft_putstr("\") !\n");
		i++;
	}
}

void	swap_list_items(t_carriage **frst, t_carriage *crnt,
		t_carriage *mem[4])
{
	while (crnt)
	{
		if (crnt->next != NULL &&
				crnt->unic_num_plr < crnt->next->unic_num_plr)
		{
			mem[1] = crnt;
			mem[2] = crnt->next;
			mem[3] = crnt->next->next;
			mem[2]->next = mem[1];
			mem[1]->next = mem[3];
			if (mem[0] != NULL)
				mem[0]->next = mem[2];
			else
				*frst = mem[2];
			crnt = mem[2];
		}
		mem[0] = crnt;
		crnt = crnt->next;
	}
}

void	sorting_list_carriage(t_carriage **frst)
{
	t_carriage	*crnt;
	t_carriage	*mem[4];
	int			i;

	i = 0;
	ft_bzero(mem, 4);
	while (i <= MAX_PLAYERS)
	{
		crnt = *frst;
		mem[0] = NULL;
		swap_list_items(frst, crnt, mem);
		i++;
	}
}
