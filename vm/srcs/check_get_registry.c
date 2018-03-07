/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_get_registry.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 15:45:53 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/25 15:48:57 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_get_registry(t_process *process, char type[3], int *param,
		int dest)
{
	int		reg;
	int		i;

	reg = 0;
	i = 0;
	while (i < process->op->param_num)
	{
		if (type[i++] == T_REG)
			reg++;
	}
	if (dest)
		reg--;
	i = 0;
	while (i < process->op->param_num)
	{
		if (type[i] == T_REG)
		{
			if (param[i] < 1 || param[i] > REG_NUMBER)
				return (0);
			if (reg-- > 0)
				param[i] = hex_to_dec(process->regs[param[i] - 1], REG_SIZE);
		}
		i++;
	}
	return (1);
}
