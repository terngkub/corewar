/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 14:53:34 by arobion           #+#    #+#             */
/*   Updated: 2018/03/17 14:42:02 by arobion          ###   ########.fr       */
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
	ft_strdel(&arn->mem);
	ft_strdel(&arn->color);
	while (i < arn->nb_players)
	{
		ft_strdel(&arn->players[i].name);
		ft_strdel(&arn->players[i].comment);
		i++;
	}
	free(arn->players);
	process_free(arn->process);
}

int		free_mem_err(t_arena arn)
{
	ft_strdel(&arn.mem);
	ft_strdel(&arn.color);
	ft_dprintf(2, "ERROR in header \nLao-Tseu a dit : "\
			"\"L'échec est le fondement de la réussite.\"\n");
	return (0);
}

int		free_arena_err(t_arena arn)
{
	ft_strdel(&arn.mem);
	ft_strdel(&arn.color);
	return (write_usage());
}
