/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:55:23 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/27 14:46:29 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	get_sti_param(t_arena *arn, t_process *process,
		char type[3], int param[3])
{
	int		position;
	int		i;

	position = 2;
	i = 0;
	while (i < 3)
	{
		if (type[i] == T_REG)
		{
			param[i] = read_mem(arn, (process->pc + position) % MEM_SIZE, 1);
			position += 1;
		}
		else if (type[i] == T_DIR)
		{
			param[i] = get_direct_2(arn, process, position, 1);
			position += 2;
		}
		else if (type[i] == T_IND)
		{
			param[i] = get_indirect(arn, process, position, 1);
			position += 2;
		}
		i++;
	}
}

void		sti(t_arena *arn, t_process *process)
{
	char	type[3];
	int		param[3];
	int		index;

	if (check_param_type(arn, process, type))
	{
		get_sti_param(arn, process, type, param);
		if (check_get_registry(process, type, param, 0))
		{
			index = (param[1] + param[2]) % IDX_MOD;
			set_mem(arn, (process->pc + index) % MEM_SIZE, param[0],\
					process->color);
		}
	}
	process->pc = (process->pc + get_fail_pos(process, type)) % MEM_SIZE;
}
