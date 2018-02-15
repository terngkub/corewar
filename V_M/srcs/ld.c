/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:57:02 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/15 22:08:52 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	load_to_registry(int value, char *registry)
{
	int		i;
	
	i = 3;
	while (i >= 0)
	{
		registry[i] = value % 256;
		value /= 256;
		i--;
	}
}

void	ld(t_arena *arn, t_process *process)
{
	int		opc;
	int		param[2];
	int		index;
	int		move;

	opc = hex_to_dec(&arn->mem[(process->pc + 1) % MEM_SIZE], 1);
	if (opc != 144 && opc != 208)
	{
		process->pc = (process->pc + 1) % MEM_SIZE;
		return;
	}
	move = 0;
	if (opc == 144)
	{
		param[0] = hex_to_dec(&arn->mem[(process->pc + 2) % MEM_SIZE], 4);
		param[1] = hex_to_dec(&arn->mem[(process->pc + 6) % MEM_SIZE], 1);
		move = 7;
	}
	else if (opc == 208)
	{
		index = hex_to_dec(&arn->mem[(process->pc + 2) % MEM_SIZE], 2);
		index = (process->pc + index) % MEM_SIZE;
		param[0] = hex_to_dec(&arn->mem[index % MEM_SIZE], 4);
		param[0] = param[0] % MEM_SIZE;
		param[1] = hex_to_dec(&arn->mem[(process->pc + 4) % MEM_SIZE], 1);
		move = 5;
	}
	if (param[1] >= 1 && param[1] <= REG_NUMBER)
	{
		print_registry(process->regs);
		load_to_registry(param[0], process->regs[param[1] - 1]);
		print_registry(process->regs);
	}
	process->pc = (process->pc + move) % MEM_SIZE;
}
