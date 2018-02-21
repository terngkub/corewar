/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 20:15:50 by arobion           #+#    #+#             */
/*   Updated: 2018/02/21 18:47:13 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	zjmp(t_arena *arn, t_process *process)
{
	int		new_pc;

	if (process->carry == 1)
	{
		new_pc = (process->pc + get_direct_2(arn, process, 1, 0)) % MEM_SIZE;
		process->pc = new_pc;
	}
	else
		process->pc = (process->pc + 3) % MEM_SIZE;
}
