/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:55:23 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/18 21:50:04 by nkamolba         ###   ########.fr       */
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

void	sti(t_arena *arn, t_process *process)
{
	char	type[3];
	int		position;
	int		param[3];
	int		index;

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
		param[1] = get_registry(arn, process, position);
		position += 1;
	}
	else if (type[1] == T_DIR)
	{
		param[1] = get_direct_2(arn, process, position, 0);
		position += 2;
	}
	else if (type[1] == T_IND)
	{
		param[1] = get_indirect(arn, process, position, 0);
		position += 2;
	}
	if (type[2] == T_DIR)
	{
		param[2] = get_direct_2(arn, process, position, 0);
		position += 2;
	}
	else if (type[2] == T_REG)
	{
		param[2] = get_registry(arn, process, position);
		position += 1;
	}
	index = (param[1] + param[2]) % 65536;
	ft_printf("%d %d %d %d %d\n", param[0], param[1], param[2], index, (process->pc + index) % MEM_SIZE);
	set_mem(arn, (process->pc + index) % MEM_SIZE, param[0]);
	process->pc = (process->pc + position) % MEM_SIZE;
}
