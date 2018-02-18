/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 22:10:54 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/18 22:14:56 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	set_registry(char *registry, int value)
{
	unsigned int	u_value;
	int				i;

	u_value = (unsigned int)value;
	i = REG_SIZE - 1;
	while (i >= 0)
	{
		registry[i] = u_value % 256;
		u_value /= 256;
		i--;
	}
}

/*
void	set_registry_bymem(t_arena *arn, t_process *process, int pos, int value)
{
	get_registry(arn, process, pos);

}
*/

void	set_mem(t_arena *arn, int index, int value)
{
	unsigned int	u_value;
	int				i;

	index = handle_idx(index);
	u_value = (unsigned int)value;
	i = DIR_SIZE - 1;
	while (i >= 0)
	{
		arn->mem[(index + i) % MEM_SIZE] = u_value % 256;
		u_value /= 256;
		i--;
	}
}
