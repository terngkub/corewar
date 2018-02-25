/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 14:57:15 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/25 14:57:58 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	modif_carry(t_process *process, char type[3], int value)
{
	if (type[0] != T_REG || type[1] != T_REG)
		if (value == 0)
		{
			process->carry = 1;
			return ;
		}
	process->carry = 0;
}

static void	get_ldi_param(t_arena *arn, t_process *process,
		char type[3], int param[3])
{
	int		position;
	int		i;

	position = 2;
	i = 0;
	while (i < 3)
	{
		if (type[0] == T_REG)
		{
			param[0] = read_mem(arn, (process->pc + position) % MEM_SIZE, 1);
			position += 1;
		}
		else if (type[0] == T_DIR)
		{
			param[0] = get_direct_2(arn, process, position, 1);
			position += 2;
		}
		else if (type[0] == T_IND)
		{
			param[0] = get_indirect(arn, process, position, 1);
			position += 2;
		}
		i++;
	}
}

void		ldi(t_arena *arn, t_process *process, int l)
{
	char	type[3];
	int		param[3];
	int		index;
	int		value;

	if (check_param_type(arn, process, type))
	{
		get_ldi_param(arn, process, type, param);
		if (check_get_registry(process, type, param, 1))
		{
			index = param[0] + param[1];
			if (l == 0)
				index %= IDX_MOD;
			value = read_mem(arn, (process->pc + index) % MEM_SIZE, DIR_SIZE);
			modif_carry(process, type, value);
			set_registry(process->regs[param[2] - 1], value);
		}
	}
	process->pc = (process->pc + get_fail_pos(process, type)) % MEM_SIZE;
}
