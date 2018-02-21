/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:57:49 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/21 16:01:39 by nkamolba         ###   ########.fr       */
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
		str[i] = arn->mem[((unsigned int)index + i) % MEM_SIZE];
		i++;
	}
	value = hex_to_dec(str, len);
	free(str);
	return (value);
}

int	handle_idx(int value)
{
	int 			i;
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

int		check_get_registry(t_process *process, char type[3], int *param, int dest)
{
	int		reg;
	int		i;

	reg = 0;
	i = 0;
	while (i < process->op->param_num)
	{
		if (type[i++] == T_REG)
			reg++;
	}
	if (dest)
		reg--;
	i = 0;
	while (i < process->op->param_num)
	{
		if (type[i] == T_REG)
		{
			if (param[i] < 1 || param[i] > REG_NUMBER)
				return (0);
			if (reg-- > 0)
				param[i] = hex_to_dec(process->regs[param[i] - 1], REG_SIZE);
		}
		i++;
	}
	return (1);
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
	l = 0;
	/*
	if (l == 0)
		value = handle_idx(value);
		*/
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
	value_index = read_mem(arn, link_index, IND_SIZE);
	if (l == 0)
		value_index = handle_idx(value_index);
	value_index = (process->pc + value_index) % MEM_SIZE;
	value = read_mem(arn, value_index, DIR_SIZE);
	return (value);
}
