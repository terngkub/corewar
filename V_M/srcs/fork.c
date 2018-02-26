/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:22:31 by arobion           #+#    #+#             */
/*   Updated: 2018/02/26 15:37:33 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		cpy_regs(t_process *curr, t_process *lst)
{
	int		i;
	int		j;

	i = 0;
	while (i < REG_NUMBER)
	{
		j = 0;
		while (j < REG_SIZE)
		{
			lst->regs[i][j] = curr->regs[i][j];
			j++;
		}
		i++;
	}
}

t_process	*cpy_process(t_process *curr, t_arena *arn, int new_pc)
{
	t_process	*lst;
	int			i;

	i = 0;
	if (!(lst = (t_process*)malloc(sizeof(t_process))))
		exit(0);
	lst->alive = curr->alive;
	lst->opc = arn->mem[new_pc];
	lst->op = get_op(arn->mem[new_pc]);
	lst->cycle_to_wait = arn->nb_cycle + opc_nb_cycle(lst->opc);
	lst->pc = new_pc;
	lst->carry = curr->carry;
	lst->color = curr->color;
	if (!(lst->regs = (char**)malloc(sizeof(char*) * (REG_NUMBER))))
		exit(0);
	while (i < REG_NUMBER)
	{
		if (!(lst->regs[i] = (char*)malloc(sizeof(char) * REG_SIZE)))
			exit(0);
		i++;
	}
	lst->next = NULL;
	cpy_regs(curr, lst);
	return (lst);
}

void		ft_fork_front(t_process **begin_list, t_process *curr,\
		t_arena *arn, int new_pc)
{
	t_process	*lst;

	if (*begin_list)
	{
		lst = cpy_process(curr, arn, new_pc);
		lst->next = *begin_list;
		*begin_list = lst;
	}
	else
		exit(0);
}

void		ft_fork(t_arena *arn, t_process *process, int l)
{
	int		new_pc;

	new_pc = (process->pc + get_direct_2(arn, process, 1, l)) % MEM_SIZE;
	ft_fork_front(&arn->process, process, arn, new_pc);
	process->pc = (process->pc + 3) % MEM_SIZE;
}
