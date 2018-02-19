/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 22:39:50 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/19 18:04:14 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	check_param_type(t_arena *arn, t_process *process, char type[3])
{
	char	*rule;
	int		byte_code;
	int		i;

	rule = process->op->param_type;
	byte_code = read_mem(arn, (process->pc + 1) % MEM_SIZE, 1);
	type[0] = (byte_code / 64) % 4;
	type[1] = (byte_code / 16) % 4;
	type[2] = (byte_code / 4) % 4;
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
