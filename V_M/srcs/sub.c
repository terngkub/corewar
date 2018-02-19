/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 21:23:14 by arobion           #+#    #+#             */
/*   Updated: 2018/02/19 17:08:57 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_ocp_sub(char ocp)
{
	int		i;
	char	test;

	i = 0;
	test = ocp >> 6;
	if (test != 1)
		i++;
	test = ocp << 2;
	test = test >> 6;
	if (test != 1)
		i++;
	test = ocp << 4;
	test = test >> 6;
	if (test != 1)
		i++;
	if (i != 0)
		return (0);
	return (1);
}

int		check_sub_param(t_arena *arn, t_process *process)
{
	if (check_ocp_sub(arn->mem[process->pc]) == 0)
		return (0);
	if (arn->mem[(process->pc + 1) % MEM_SIZE] >= REG_NUMBER)
		return (0);
	if (arn->mem[(process->pc + 2) % MEM_SIZE] >= REG_NUMBER)
		return (0);
	if (arn->mem[(process->pc + 3) % MEM_SIZE] >= REG_NUMBER)
		return (0);
	return (1);
}

void	sub(t_arena *arn, t_process *process)
{
	int		res;

	process->pc = (process->pc + 1) % MEM_SIZE;
	if (!(check_sub_param(arn, process)))
		return ;
	res = x_char_to_int(process->regs[arn->mem[(process->pc + 1)\
			% MEM_SIZE] - 1], REG_SIZE);
	res -= x_char_to_int(process->regs[arn->mem[(process->pc + 2)\
			% MEM_SIZE] - 1], REG_SIZE);
	int_to_x_char(process->regs[arn->mem[(process->pc + 3)\
			% MEM_SIZE] - 1], REG_SIZE, res);
	process->pc = (process->pc + 4) % MEM_SIZE;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
