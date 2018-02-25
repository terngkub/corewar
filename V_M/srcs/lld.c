/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 15:05:27 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/25 15:08:09 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	get_lld_param(t_arena *arn, t_process *process,
		char type[3], int param[2])
{
	int		position;

	position = 2;
	if (type[0] == T_DIR)
	{
		param[0] = get_direct_4(arn, process, position);
		position += 4;
	}
	else if (type[0] == T_IND)
	{
		param[0] = get_indirect(arn, process, position, 1);
		position += 2;
	}
	param[1] = read_mem(arn, (process->pc + position) % MEM_SIZE, 1);
	if (param[1] == 0)
		process->carry = 1;
	position += 1;
}

void		lld(t_arena *arn, t_process *process)
{
	char	type[3];
	int		param[2];

	if (check_param_type(arn, process, type))
	{
		get_lld_param(arn, process, type, param);
		if (check_get_registry(process, type, param, 2))
		{
			if (type[0] == T_IND)
			{
				param[0] = param[0] >> 16;
				param[0] = param[0] >= 0 ? param[0] & 0x0000ffff
					: param[0] | 0xffff0000;
				process->carry = 0;
			}
			process->carry = param[0] == 0 ? 1 : 0;
			set_registry(process->regs[param[1] - 1], param[0]);
		}
	}
	process->pc = (process->pc + get_fail_pos(process, type)) % MEM_SIZE;
}
