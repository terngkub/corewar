/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:55:23 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/16 22:41:00 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	st(t_arena *arn, t_process *process)
{
	char	param_type[3];

	param = {1, 1 | 2};
	opc = hex_to_dec(&arn->mem[(process->pc + 1) % MEM_SIZE], 1);
	if (check_param(opc, param_type))
	{
		process->pc = (process->pc + 1) % MEM_SIZE;
		return ;
	}
	move = 0;


}
