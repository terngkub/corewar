/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:55:23 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/17 17:56:41 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	st(t_arena *arn, t_process *process)
{
	char	type[3];
	int		position;
	int		param[2];

	if (!check_param_type(arn, process, type))
	{
		process->pc = (process->pc + 1) % MEM_SIZE;
		return ;
	}
	position = 2;
	param[0] = get_registry(arn, process, position);
	position += 1;
	if (type[1] == T_REG)
	{
		param[1] = read_mem(arn, (process->pc + position) % MEM_SIZE, 1); 
		set_registry(process->regs[param[1] - 1], param[0]);
		position += 1;
	}
	else if (type[1] == T_IND)
	{
		param[1] = read_mem(arn, (process->pc + position) % MEM_SIZE, 2); 
		set_mem(arn, (process->pc + param[1]) % MEM_SIZE, param[0]);
		position += 2;
	}
	process->pc = (process->pc + position) % MEM_SIZE;
}
