/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:57:02 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/17 17:07:35 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ld(t_arena *arn, t_process *process)
{
	char	type[3];
	int		position;
	int		param[2];

	if (!check_param_type(arn, process, type))
	{
		process->pc = (process->pc + 1) % MEM_SIZE;
		return;
	}
	position = 2;
	if (type[0] == T_DIR)
	{
		param[0] = get_direct_4(arn, process, position);
		position += 4;
	}
	else if (type[0] == T_IND)
	{
		param[0] = get_indirect(arn, process, position);
		position += 2;
	}
	param[1] = read_mem(arn, (process->pc + position) % MEM_SIZE, 1);
	position += 1;
	if (param[1] >= 1 && param[1] <= REG_NUMBER)
	{
		ft_printf("before\n");
		print_registry(process->regs);
		set_registry(process->regs[param[1] - 1], param[0]);
		ft_printf("\nafter\n");
		print_registry(process->regs);
	}
	process->pc = (process->pc + position) % MEM_SIZE;
}
