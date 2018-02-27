/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:31:37 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/27 16:10:22 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	do_instruction2(t_arena *arn, t_process *process)
{
	if (process->opc == 10)
		ldi(arn, process, 0);
	else if (process->opc == 11)
		sti(arn, process);
	else if (process->opc == 12)
		ft_fork(arn, process, 0);
	else if (process->opc == 13)
		lld(arn, process);
	else if (process->opc == 14)
		ldi(arn, process, 1);
	else if (process->opc == 15)
		ft_fork(arn, process, 1);
	else if (process->opc == 16)
		aff(arn, process);
	else
		process->pc = (process->pc + 1) % MEM_SIZE;
}

void	do_instruction(t_arena *arn, t_process *process)
{
	if (process->opc == 1)
		live(arn, process);
	else if (process->opc == 2)
		ld(arn, process, 0);
	else if (process->opc == 3)
		st(arn, process);
	else if (process->opc == 4)
		add(arn, process);
	else if (process->opc == 5)
		sub(arn, process);
	else if (process->opc == 6)
		bitwise(arn, process, '&');
	else if (process->opc == 7)
		bitwise(arn, process, '|');
	else if (process->opc == 8)
		bitwise(arn, process, '^');
	else if (process->opc == 9)
		zjmp(arn, process);
	else
		do_instruction2(arn, process);
}

void	run_processes(t_arena *arn)
{
	t_process	*process;
	int			i;
	int			inst_cycle;

	process = arn->process;
	i = 1;
	while (process)
	{
		if (!process->op)
		{
			process->opc = arn->mem[process->pc];
			process->op = get_op(process->opc);
			inst_cycle = process->op ? process->op->cycle : 1;
			process->cycle_to_wait = arn->nb_cycle + inst_cycle - 1;
		}
		if (process->cycle_to_wait == arn->nb_cycle)
		{
			do_instruction(arn, process);
			process->op = NULL;
		}
		process = process->next;
		i++;
	}
}

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

void	find_winner(t_arena *arn)
{
	int		i;
	int		winner;

	i = arn->nb_players - 1;
	winner = i + 1;
	while (i >= 0)
	{
		if (arn->players[i].number == arn->winner)
			winner = i + 1;
		i--;
	}
	ft_printf("Contestant %d, \"%s\", has won !\n",\
			arn->players[winner - 1].number, arn->players[winner - 1].name);
}

void	run_cycle(t_arena *arn, int dump, int display)
{
	int		next_cycle_to_die;
	int		cycle_to_die;
	int		proc;

	(void)display;
	cycle_to_die = CYCLE_TO_DIE;
	next_cycle_to_die = CYCLE_TO_DIE;
	if (display)
		ft_visu(arn);
	else
		while ((proc = nb_of_process(&(arn->process))))
		{
			if (arn->nb_cycle == next_cycle_to_die)
				kill_and_refresh_processes(arn, &(arn->process),\
						&next_cycle_to_die, &cycle_to_die);
			run_processes(arn);
			if (dump == arn->nb_cycle)
				return (dump_mem(*arn));
			arn->nb_cycle++;
		}
	find_winner(arn);
	freeall(arn);
}
