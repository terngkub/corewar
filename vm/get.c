/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:57:49 by nkamolba          #+#    #+#             */
/*   Updated: 2018/03/16 20:22:29 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	read_mem(t_arena *arn, int index, int len)
{
	char			*str;
	int				i;
	int				value;

	if (!(str = ft_strnew(len)))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		str[i] = arn->mem[((unsigned int)index + i) % MEM_SIZE];
		i++;
	}
	value = hex_to_dec(str, len);
	ft_strdel(&str);
	return (value);
}

int	handle_idx(int value)
{
	int				i;
	unsigned int	cut_point;
	unsigned int	u_value;

	cut_point = 256;
	i = 1;
	while (i++ < IND_SIZE)
		cut_point *= 256;
	u_value = (unsigned int)value;
	u_value = u_value % cut_point;
	if (u_value < cut_point / 2)
		u_value = u_value % IDX_MOD;
	else
		u_value = MEM_SIZE - ((cut_point - u_value) % IDX_MOD);
	return (u_value);
}

int	get_direct_2(t_arena *arn, t_process *process, int pos, int l)
{
	int				value_index;
	int				value;

	value_index = (process->pc + pos) % MEM_SIZE;
	value = read_mem(arn, value_index, IND_SIZE);
	if (l == 0)
		value = handle_idx(value);
	return (value);
}

int	get_direct_4(t_arena *arn, t_process *process, int pos)
{
	int				value_index;
	int				value;

	value_index = (process->pc + pos) % MEM_SIZE;
	value = read_mem(arn, value_index, DIR_SIZE);
	return (value);
}

int	get_indirect(t_arena *arn, t_process *process, int pos, int l)
{
	int				link_index;
	int				value_index;
	int				value;

	link_index = (process->pc + pos) % MEM_SIZE;
	value_index = read_mem(arn, link_index, IND_SIZE);
	if (l == 0)
		value_index = handle_idx(value_index);
	value_index = (process->pc + value_index) % MEM_SIZE;
	value = read_mem(arn, value_index, DIR_SIZE);
	return (value);
}
