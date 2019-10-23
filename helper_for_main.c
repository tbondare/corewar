/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_for_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:25:51 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/22 16:26:33 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void	write_introduction(t_carriage *frst)
{
	t_carriage *crn;

	crn = frst;
	ft_putstr("Introduction contestants...\n");
	while (crn)
	{
		ft_putstr("* Player ");
		ft_putnbr(crn->unic_num_plr);
		ft_putstr(", weighting ");
		ft_putnbr(crn->header.prog_size);
		ft_putstr(" bytes, \"");
		ft_putstr(crn->header.prog_name);
		ft_putstr("\" (\"");
		ft_putstr(crn->header.comment);
		ft_putstr("\") ! \n");
		crn = crn->next;
	}
}

void swap_list_items(t_carriage **frst, t_carriage	*crnt, t_carriage *mem[4])
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
