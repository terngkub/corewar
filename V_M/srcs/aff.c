/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:57:25 by arobion           #+#    #+#             */
/*   Updated: 2018/02/16 17:43:06 by arobion          ###   ########.fr       */
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

void	aff(t_arena *arn, t_process *process)
{
	int		to_aff;
	int		pos;

	pos = arn->mem[process->pc + 2] - 1;
	to_aff = x_char_to_int(process->regs[pos], REG_SIZE);
	to_aff %= 256;
	write(1, "Aff : ", 6);
	write(1, &to_aff, 1);
	write(1, "\n", 1);
	process->pc += 3;
	if (to_aff == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
