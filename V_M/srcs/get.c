/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:57:49 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/17 19:41:55 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	read_mem(t_arena *arn, int index, int len)
{
	char	*str;
	int		i;
	int		value;

	if (!(str = ft_strnew(len)))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		str[i] = arn->mem[(index + i) % MEM_SIZE];
		i++;
	}
	value = hex_to_dec(str, len);
	return (value);
}

int	get_registry(t_arena *arn, t_process *process, int pos)
{
	int		value_index;
	int		reg_nb;
	int		value;

	value_index = (process->pc + pos) % MEM_SIZE;
	reg_nb = read_mem(arn, value_index, 1);
	value = hex_to_dec(process->regs[reg_nb - 1], REG_SIZE);
	return (value);
}

int	get_direct_2(t_arena *arn, t_process *process, int pos, int l)
{
	int	value_index;
	int	value;

	value_index = (process->pc + pos) % MEM_SIZE;
	value = read_mem(arn, value_index, IND_SIZE);
	if (l == 0 && value < 0)
	{
		if (value < 0)
			value = -((-value) % IDX_MOD);
		else
			value = value % IDX_MOD;
	}
	return (value);
}

int	get_direct_4(t_arena *arn, t_process *process, int pos)
{
	int	value_index;
	int	value;

	value_index = (process->pc + pos) % MEM_SIZE;
	value = read_mem(arn, value_index, DIR_SIZE);
	return (value);
}


int	get_indirect(t_arena *arn, t_process *process, int pos, int l)
{
	int	link_index;
	int	value_index;
	int	value;
	
	link_index = (process->pc + pos) % MEM_SIZE;
	ft_printf("link_index: %d\n", link_index);
	value_index = read_mem(arn, link_index, IND_SIZE);
	if (l == 0 && value_index < 0)
	{
		if (value_index < 0)
			value_index = -((-value_index) % IDX_MOD);
		else
			value_index = value_index % IDX_MOD;
	}
	value_index = (process->pc + value_index) % MEM_SIZE;
	ft_printf("value_index: %d\n", value_index);
	value = read_mem(arn, value_index, DIR_SIZE);
	return (value);
}
