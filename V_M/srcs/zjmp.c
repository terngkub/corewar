/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 20:15:50 by arobion           #+#    #+#             */
/*   Updated: 2018/02/17 20:32:53 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	zjmp(t_arena *arn, t_process *process)
{
	int		new_pc;

	if (carry == 1)
		new_pc = (process->pc + get_direct_2(arn, process, 1, 1));
}
