/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:43:46 by arobion           #+#    #+#             */
/*   Updated: 2018/02/16 15:50:23 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_process	*lst_new_process(int opc, int cycle, int pc)
{
	t_process	*lst;
	int			i;

	i = 0;
	if (!(lst = (t_process*)malloc(sizeof(t_process))))
		exit(0);
	lst->alive = 0;
	lst->opc = opc;
	lst->cycle_to_wait = cycle;
	lst->pc = pc;
	lst->carry = 0;
	if (!(lst->regs = (char**)malloc(sizeof(char*) * (REG_NUMBER))))
		exit(0);
	while (i < REG_NUMBER)
	{
		if (!(lst->regs[i] = (char*)malloc(sizeof(char) * REG_SIZE)))
			exit(0);
		i++;
	}
	lst->next = NULL;
	return (lst);
}

void		lst_pushfront_process(t_process **begin_list, int opc,\
		int cycle, int pc)
{
	t_process	*lst;

	if (*begin_list)
	{
		lst = lst_new_process(opc, cycle, pc);
		lst->next = *begin_list;
		*begin_list = lst;
	}
	else
		*begin_list = lst_new_process(opc, cycle, pc);
}

void		init_process(t_arena arn, t_process **begin_list)
{
	int			i;
	int			start;
	t_process	*lst;

	i = 0;
	while (i < arn.nb_players)
	{
		start = start_of_input(i + 1, arn.nb_players);
		lst_pushfront_process(begin_list, arn.mem[start],\
				opc_nb_cycle(arn.mem[start]), start);
		i++;
	}
	lst = *begin_list;
	i = arn.nb_players - 1;
	while (lst)
	{

		int_to_x_char(lst->regs[0], REG_SIZE, -arn.players[i].number);
		i--;
		lst = lst->next;
	}
}
