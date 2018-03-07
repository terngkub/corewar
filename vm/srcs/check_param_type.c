/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 22:39:50 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/25 14:29:27 by nkamolba         ###   ########.fr       */
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
		if (type[i] == 3)
			type[i] = 4;
	i = -1;
	while (++i < 3)
		if (rule[i] != 0 && !(type[i] & rule[i]))
			return (0);
	return (1);
}

int	get_fail_pos(t_process *process, char type[3])
{
	int		ret;
	int		i;

	ret = 2;
	i = 0;
	while (i < process->op->param_num)
	{
		if (type[i] == 1)
			ret += 1;
		else if (type[i] == 2)
			ret += process->op->direct_len;
		else if (type[i] == 4)
			ret += 2;
		i++;
	}
	return (ret);
}
