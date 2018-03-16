/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:15:54 by arobion           #+#    #+#             */
/*   Updated: 2018/03/16 20:22:02 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		nb_of_process(t_process **begin_list)
{
	t_process	*lst;
	int			i;

	lst = *begin_list;
	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	change_cycle_to_die(t_arena *arn, int *next, int *die)
{
	int		lives;

	lives = arn->lives;
	if (lives < NBR_LIVE)
	{
		arn->nb_checks += 1;
		if (arn->nb_checks == MAX_CHECKS)
		{
			*die -= CYCLE_DELTA;
			if (*die < 0)
				*die = 1;
			arn->nb_checks = 0;
		}
	}
	else
	{
		arn->nb_checks = 0;
		*die -= CYCLE_DELTA;
		if (*die < 0)
			*die = 1;
	}
	*next += *die;
	arn->lives = 0;
}

void	kill_dead_processes(t_process **begin_list)
{
	t_process	*lst;
	t_process	*tmp;

	while (*begin_list && (*begin_list)->alive == 0)
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		free_one_process(&tmp);
		free(tmp);
	}
	lst = *begin_list;
	while (lst && lst->next)
	{
		if (lst->next->alive == 0)
		{
			tmp = lst->next;
			lst->next = tmp->next;
			free_one_process(&tmp);
			free(tmp);
		}
		else if (lst->next)
			lst = lst->next;
	}
}

void	refresh_processes(t_process **begin_list, t_arena *arn)
{
	t_process	*lst;
	int			i;

	i = 0;
	lst = *begin_list;
	while (lst)
	{
		lst->alive = 0;
		lst = lst->next;
	}
	while (i < arn->nb_players)
	{
		arn->players[i].nb_live = 0;
		i++;
	}
}

void	kill_and_refresh_processes(t_arena *arn, t_process **begin_list,\
		int *next, int *die)
{
	change_cycle_to_die(arn, next, die);
	kill_dead_processes(begin_list);
	refresh_processes(begin_list, arn);
}
