/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:57:02 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/21 20:33:36 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ld(t_arena *arn, t_process *process, int l)
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
	position += 1;
	if (check_get_registry(process, type, param, 2))
	{
		set_registry(process->regs[param[1] - 1], param[0]);
		if (param[0] == 0)
			process->carry = 1;
		else
			process->carry = 0;
		process->pc = (process->pc + position) % MEM_SIZE;
	}
}

void	lld(t_arena *arn, t_process *process)
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
	if (check_get_registry(process, type, param, 2))
	{
		if (type[0] == T_IND)
		{
			param[0] = param[0] >> 16;
			if (param[0] >= 0)
				param[0] = param[0] & 0x0000ffff;
			else
				param[0] = param[0] | 0xffff0000;
		}
		set_registry(process->regs[param[1] - 1], param[0]);
	}
	process->pc = (process->pc + position) % MEM_SIZE;
	//print_registry(process->regs);
}

void	modif_carry(t_process *process, char type[3], int value)
{
	if (type[0] != T_REG || type[1] != T_REG)
		if (value == 0)
		{
			process->carry = 1;
			return ;
		}
	process->carry = 0;
}

void	ldi(t_arena *arn, t_process *process, int l)
{
	char	type[3];
	int		position;
	int		param[3];
	int		index;
	int		value;

	if (!check_param_type(arn, process, type))
	{
		process->pc = (process->pc + 1) % MEM_SIZE;
		return;
	}
	position = 2;
	if (type[0] == T_REG)
	{
		param[0] = read_mem(arn, (process->pc + position) % MEM_SIZE, 1);
		position += 1;
	}
	else if (type[0] == T_DIR)
	{
		param[0] = get_direct_2(arn, process, position, l);
		position += 2;
	}
	else if (type[0] == T_IND)
	{
		param[0] = get_indirect(arn, process, position, l);
		position += 2;
	}
	if (type[1] == T_DIR)
	{
		param[1] = get_direct_2(arn, process, position, l);
		position += 2;
	}
	else if (type[1] == T_REG)
	{
		param[1] = read_mem(arn, (process->pc + position) % MEM_SIZE, 1);
		position += 1;
	}
	param[2] = read_mem(arn, (process->pc + position) % MEM_SIZE, 1);
	position += 1;
	if (check_get_registry(process, type, param, 1))
	{
		index = (param[0] + param[1]) % 65536;
		value = read_mem(arn, (process->pc + index) % MEM_SIZE, DIR_SIZE);
		modif_carry(process, type, value);
		set_registry(process->regs[param[2] - 1], value);
	}
	process->pc = (process->pc + position) % MEM_SIZE;
	//print_registry(process->regs);
}
