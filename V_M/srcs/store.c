/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:55:23 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/21 16:33:02 by arobion          ###   ########.fr       */
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
	if ((param[0] = get_registry(arn, process, position)) == -1)
	{
		process->pc = (process->pc + 1) % MEM_SIZE;
		return ;
	}
	position += 1;
	if (type[1] == T_REG)
	{
		param[1] = read_mem(arn, (process->pc + position) % MEM_SIZE, 1); 
		if (param[1] - 1 < 0 || param[1] - 1 >= REG_NUMBER)
		{
			process->pc = (process->pc + 1) % MEM_SIZE;
			return ;
		}
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

void	set_in_mem(t_arena *arn, int index, int value)
{
	unsigned int	u_value;
	int				i;

	u_value = (unsigned int)value;
	i = DIR_SIZE - 1;
	while (i >= 0)
	{
		arn->mem[((unsigned int)index + i) % MEM_SIZE] = u_value % 256;
		u_value /= 256;
		i--;
	}
}

void	sti(t_arena *arn, t_process *process)
{
	char	type[3];
	int		position;
	int		param[3];
	int		index;
	int		i;

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
			param[i] = get_direct_2(arn, process, position, 0);
			position += 2;
		}
		else if (type[i] == T_IND)
		{
			param[i] = get_indirect(arn, process, position, 0);
			position += 2;
		}
		i++;
	}
	if (check_get_registry(process, type, param, 0))
	{
		index = (param[1] + param[2]) % 65536;
		set_in_mem(arn, (process->pc + index) % MEM_SIZE, param[0]);
	}
	process->pc = (process->pc + position) % MEM_SIZE;
}
