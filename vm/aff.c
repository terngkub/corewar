/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:57:25 by arobion           #+#    #+#             */
/*   Updated: 2018/03/03 16:23:27 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		change_move_pc(int val)
{
	if (val == 0)
		return (0);
	if (val == 1)
		return (1);
	if (val == 2)
		return (4);
	if (val == 3)
		return (2);
	return (0);
}

int		verif_ocpar_aff(t_process *process, t_arena *arn, int *j)
{
	unsigned char	bit_value;
	int				i;
	unsigned char	test;

	i = (process->pc + 1) % MEM_SIZE;
	test = arn->mem[i];
	bit_value = test >> 6;
	*j = change_move_pc(bit_value);
	if (bit_value == 1)
		return (1);
	else
		return (0);
}

void	aff(t_arena *arn, t_process *process)
{
	int		to_aff;
	int		pos;
	int		move_pc;

	move_pc = 0;
	pos = arn->mem[(process->pc + 2) % MEM_SIZE] - 1;
	if (verif_ocpar_aff(process, arn, &move_pc) == 1 &&\
			(pos < REG_NUMBER && pos >= 0))
	{
		to_aff = x_char_to_int(process->regs[pos], REG_SIZE);
		to_aff %= 256;
		if (arn->displays != 1)
		{
			write(1, "Aff: ", 5);
			write(1, &to_aff, 1);
			write(1, "\n", 1);
		}
		process->pc = (process->pc + 3) % MEM_SIZE;
		if (to_aff == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	else
		process->pc = (process->pc + 2 + move_pc) % MEM_SIZE;
}
