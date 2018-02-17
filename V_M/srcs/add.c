/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 20:32:58 by arobion           #+#    #+#             */
/*   Updated: 2018/02/17 21:22:39 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_ocp_add(char ocp)
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

int		check_add_param(t_arena *arn, t_process *process)
{
	if (check_ocp_add(arn->mem[process->pc]) == 0)
		return (0);
	if (arn->mem[(process->pc + 1) % MEM_SIZE] >= REG_NUMBER)
		return (0);
	if (arn->mem[(process->pc + 2) % MEM_SIZE] >= REG_NUMBER)
		return (0);
	if (arn->mem[(process->pc + 3) % MEM_SIZE] >= REG_NUMBER)
		return (0);
	return (1);
}

void	add(t_arena *arn, t_process *process)
{
	int		res;

	process->pc = (process->pc + 1) % MEM_SIZE;
	if (!(check_add_param(arn, process)))
		return ;
	res = x_char_to_int(process->regs[arn->mem[(process->pc + 1) % MEM_SIZE] - 1], REG_SIZE);
	res += x_char_to_int(process->regs[arn->mem[(process->pc + 2) % MEM_SIZE] - 1], REG_SIZE);
	int_to_x_char(process->regs[arn->mem[(process->pc + 3) % MEM_SIZE] - 1], REG_SIZE, res);
	process->pc = (process->pc + 4) % MEM_SIZE;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
