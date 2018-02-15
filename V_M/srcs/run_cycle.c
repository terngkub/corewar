/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:31:37 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/15 15:00:21 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	do_instruction(t_arena *arn, t_process *process)
{
	if (process->opc == 1)
		live(arn, process);
	else
		process->pc = (process->pc + 1) % MEM_SIZE;
	process->opc = arn->mem[process->pc];
	process->cycle_to_wait = arn->nb_cycle + opc_nb_cycle(arn->mem[process->pc]);
}

void	run_processes(t_arena *arn)
{
	t_process	*process;

	process = arn->process;
	while (process)
	{
		ft_printf("pc: %d\n", process->pc);
		if (process->cycle_to_wait == arn->nb_cycle)
			do_instruction(arn, process);
		process = process->next;
	}
}

void	run_cycle(t_arena *arn)
{
	while(arn->nb_cycle < 100)
	{
		ft_printf("cycle: %d\n", arn->nb_cycle);
		run_processes(arn);
		arn->nb_cycle++;
	}
}
