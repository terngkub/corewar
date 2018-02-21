/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitwise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 21:59:40 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/21 18:59:42 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	bitwise(t_arena *arn, t_process *process, char op)
{
	char	type[3];
	int		position;
	int		param[3];
	int		i;
	int		value;

	if (!check_param_type(arn, process, type))
	{
		process->pc = (process->pc + 1) % MEM_SIZE;
		return ;
	}
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
			param[i] = get_direct_4(arn, process, position);
			position += 4;
		}
		else if (type[i] == T_IND)
		{
			param[i] = get_indirect(arn, process, position, 0);
			position += 2;
		}
		i++;
	}
	if (check_get_registry(process, type, param, 1))
	{
		value = 0;
		if (op == '&')
			value = param[0] & param[1];
		else if (op == '|')
			value = param[0] | param[1];
		else if (op == '^')
			value = param[0] ^ param[1];
		if (value == 0)
			process->carry = 1;
		else
			process->carry = 0;
		set_registry(process->regs[param[2] - 1], value);
		//print_registry(process->regs);
	}
	process->pc = (process->pc + position) % MEM_SIZE;
}
