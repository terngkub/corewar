/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 17:20:28 by arobion           #+#    #+#             */
/*   Updated: 2018/02/17 17:22:36 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		long_fork(t_arena *arn, t_process *process)
{
	int		i;
	int		new_pc;

	i = 0;
	i = (process->pc + 1) % MEM_SIZE;
	new_pc = x_char_to_int(&arn->mem[i], T_DIR);
	new_pc = new_pc % MEM_SIZE;
	new_pc = new_pc % IDX_MOD;
	ft_fork_front(&arn->process, process, arn, new_pc);
	process->pc = (process->pc + 3) % MEM_SIZE;
}
