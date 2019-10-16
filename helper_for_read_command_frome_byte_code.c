/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_for_read_command_frome_byte_code.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:58:14 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/16 19:59:09 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

int	is_val_command_oper_code(int crnt_oper_code)
{
	if (crnt_oper_code > 0 && crnt_oper_code < 17)
		return (1);
	else
		return (0);
}

int	is_argum_type(t_op *info_com, t_carriage *crnt_carr)
{
	if (info_com->argum_nums == 1 && info_com->argum_types[0] == T_DIR)
	{
		crnt_carr->command.is_arg_type = 0;
		return (0);
	}
	else
		return (1);
}
