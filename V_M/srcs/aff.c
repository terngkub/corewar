/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:57:25 by arobion           #+#    #+#             */
/*   Updated: 2018/02/17 16:16:23 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_print_reg(char *str)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		ft_printf("%d\n", str[i]);
		i++;
	}
}

int		verif_ocpar_aff(t_process *process, t_arena *arn)
{
	int		bit_value;
	int		i;

	i = (process->pc + 1) & MEM_SIZE;
	bit_value = arn->mem[i] >> 6;
	if (bit_value == 1)
		return (1);
	else
		return (0);
}

void	aff(t_arena *arn, t_process *process)
{
	int		to_aff;
	int		pos;

	pos = arn->mem[(process->pc + 2) % MEM_SIZE] - 1;
	if (verif_ocpar_aff(process, arn) == 1 && pos < REG_NUMBER)
	{
		to_aff = x_char_to_int(process->regs[pos], REG_SIZE);
		to_aff %= 256;
		write(1, "Aff : ", 6);
		write(1, &to_aff, 1);
		write(1, "\n", 1);
		process->pc = (process->pc + 3) % MEM_SIZE;
		if (to_aff == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	else
		process->pc += 1;
}
