/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 14:53:34 by arobion           #+#    #+#             */
/*   Updated: 2018/02/27 15:20:06 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	free_one_process(t_process **process)
{
	int		i;

	i = 0;
	while (i < REG_NUMBER)
	{
		free((*process)->regs[i]);
		i++;
	}
	free((*process)->regs);
}

void	process_free(t_process *begin)
{
	t_process	*lst;
	t_process	*tmp;

	lst = begin;
	while (lst)
	{
		tmp = lst->next;
		free_one_process(&lst);
		free(lst);
		lst = tmp;
	}
}

void	freeall(t_arena *arn)
{
	int		i;

	i = 0;
	free(arn->mem);
	free(arn->color);
	while (i < arn->nb_players)
	{
		free(arn->players[i].name);
		free(arn->players[i].comment);
		i++;
	}
	free(arn->players);
	process_free(arn->process);
}
