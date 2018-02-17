/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 22:39:50 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/17 16:11:03 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	check_param_type(t_arena *arn, t_process *process, char rule[3], char type[3])
{
	int		pc;
	int		i;

	pc = read_mem(arn, (process->pc + 1) % MEM_SIZE, 1);
	type[0] = (pc / 64) % 4;
	type[1] = (pc / 16) % 4;
	type[2] = (pc / 4) % 4;
	ft_printf("%d %d %d\n", (int)type[0], (int)type[1], (int)type[2]);
	i = -1;
	while (++i < 3)
	{
		if (type[i] == 3)
			type[i] = 4;
		if (rule[i] != 0 && !(type[i] & rule[i]))
			return (0);
	}
	return (1);
}
