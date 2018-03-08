/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 11:11:47 by arobion           #+#    #+#             */
/*   Updated: 2018/02/27 16:21:02 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_ocp_st(unsigned char ocp, int *j)
{
	int				i;

	*j = 0;
	if ((i = valid_ocp(ocp)) == -1)
	{
		*j = modif_pc(ocp);
		return (-1);
	}
	else
	{
		*j = modif_pc(ocp);
		return (i);
	}
}

int		check_rg(int value)
{
	if (value < 1 || value > REG_NUMBER)
		return (0);
	return (1);
}

int		load_in_mem_rg(t_process *process, int rg1, int rg2)
{
	int		i;

	i = 0;
	while (i < REG_SIZE)
	{
		process->regs[rg2 - 1][i] = process->regs[rg1 - 1][i];
		i++;
	}
	process->pc = (process->pc + 3) % MEM_SIZE;
	return (0);
}

int		load_in_mem_id(t_arena *arn, t_process *process, int rg, int id)
{
	int		i;

	i = 0;
	while (i < REG_SIZE)
	{
		arn->mem[(id + i) % MEM_SIZE] = process->regs[rg - 1][i];
		arn->color[(id + i) % MEM_SIZE] = process->color;
		i++;
	}
	process->pc = (process->pc + 2 + IND_SIZE) % MEM_SIZE;
	return (0);
}

int		st(t_arena *arn, t_process *process)
{
	int		i;
	int		rg;
	int		id;
	int		move_pc;

	process->pc = (process->pc + 1) % MEM_SIZE;
	i = check_ocp_st(arn->mem[process->pc], &move_pc);
	if (i == -1)
		return (process->pc = (process->pc + 1 + move_pc) % MEM_SIZE);
	if (!(check_rg(arn->mem[(process->pc + 1) % MEM_SIZE])))
		return (process->pc = (process->pc + 1 + move_pc) % MEM_SIZE);
	if (i == 0)
		if (!(check_rg(arn->mem[(process->pc + 2) % MEM_SIZE])))
			return (process->pc = (process->pc + 1 + move_pc) % MEM_SIZE);
	rg = arn->mem[(process->pc + 1) % MEM_SIZE];
	if (i == 0)
	{
		id = arn->mem[(process->pc + 2) % MEM_SIZE];
		return (load_in_mem_rg(process, rg, id));
	}
	else
	{
		id = (process->pc - 1 + get_direct_2(arn, process, 2, 0)) % MEM_SIZE;
		return (load_in_mem_id(arn, process, rg, id));
	}
}
