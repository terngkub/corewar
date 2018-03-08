/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:57:02 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/25 15:07:08 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ld(t_arena *arn, t_process *process, int l)
{
	char	type[3];
	int		position;
	int		param[2];

	if (check_param_type(arn, process, type))
	{
		position = 2;
		if (type[0] == T_DIR)
		{
			param[0] = get_direct_4(arn, process, position);
			position += 4;
		}
		else if (type[0] == T_IND)
		{
			param[0] = get_indirect(arn, process, position, l);
			position += 2;
		}
		param[1] = read_mem(arn, (process->pc + position) % MEM_SIZE, 1);
		if (check_get_registry(process, type, param, 2))
		{
			set_registry(process->regs[param[1] - 1], param[0]);
			process->carry = param[0] == 0 ? 1 : 0;
		}
	}
	process->pc = (process->pc + get_fail_pos(process, type)) % MEM_SIZE;
}
