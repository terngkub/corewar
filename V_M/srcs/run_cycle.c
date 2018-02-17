/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:31:37 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/17 21:31:59 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	do_instruction(t_arena *arn, t_process *process)
{
	int		inst_cycle;

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
	else if (process->opc == 16)
		aff(arn, process);
	else if (process->opc == 12)
		ft_fork(arn, process);
	else if (process->opc == 13)
		ld(arn, process, 1);
	else if (process->opc == 15)
		long_fork(arn, process);
	else
		process->pc = (process->pc + 1) % MEM_SIZE;
	process->opc = arn->mem[process->pc];
	process->op = get_op(process->opc);
	inst_cycle = process->op ? process->op->cycle : 1;
	process->cycle_to_wait = arn->nb_cycle + inst_cycle;
}

void	run_processes(t_arena *arn)
{
	t_process	*process;

	process = arn->process;
	while (process)
	{
//		ft_printf("pc: %d\n", process->pc);
		if (process->cycle_to_wait == arn->nb_cycle)
			do_instruction(arn, process);
		process = process->next;
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

int		nb_lives(t_player *players, t_arena *arn)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < arn->nb_players)
	{
		ret += players[i].nb_live;
		i++;
	}
	return (ret);
}

void	change_cycle_to_die(t_arena *arn, int *next, int *die)
{
	int		lives;

	lives = nb_lives(arn->players, arn);
	if (lives < NBR_LIVE)
	{
		arn->nb_checks += 1;
		if (arn->nb_checks == MAX_CHECKS)
		{
			*die -= CYCLE_DELTA;
			arn->nb_checks = 0;
		}
	}
	else
	{
		arn->nb_checks = 0;
		*die -= CYCLE_DELTA;
	}
	*next += *die;
}

void	kill_dead_processes(t_process **begin_list)
{
	t_process	*lst;
	t_process	*tmp;
	
	while (*begin_list && (*begin_list)->alive == 0)
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(tmp);
	}
	lst = *begin_list;
	while (lst && lst->next)
	{
		if (lst->next->alive == 0)
		{
			tmp = lst->next;
			lst->next = tmp->next;
			free(tmp);
		}
		if (lst->next)
			lst = lst->next;
	}
}

void	refresh_processes(t_process **begin_list, t_arena *arn)
{
	t_process *lst;
	int		i;
	
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

void	kill_and_refresh_processes(t_arena *arn, t_process **begin_list, int *next, int *die)
{
	change_cycle_to_die(arn, next, die);
	kill_dead_processes(begin_list);
	refresh_processes(begin_list, arn);
}

void	find_winner(t_arena *arn)
{
	int		i;
	int		ret;
	int		winner;

	i = arn->nb_players - 1;
	ret = arn->players[i].last_live;
	winner = arn->nb_players;
	while (i >= 0)
	{
		if (arn->players[i].last_live > ret)
		{
			ret = arn->players[i].last_live;
			winner = i + 1;
		}
		i--;
	}
	ft_printf("Contestant %d, \"%s\", has won !\n", arn->players[winner - 1].number, arn->players[winner - 1].name);
}

void		print_test(t_arena arn)
{
	if (arn.nb_cycle == 10)
	{
		(void)arn;
		ft_printf("\n\n YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYy\n");
		print_arena(arn);
	}
}

void		run_cycle(t_arena *arn, int dump)
{
	int		next_cycle_to_die;
	int		cycle_to_die;

	cycle_to_die = CYCLE_TO_DIE;
	next_cycle_to_die = CYCLE_TO_DIE;
	while (nb_of_process(&(arn->process)))
	{
		if (arn->nb_cycle == next_cycle_to_die)
			kill_and_refresh_processes(arn, &(arn->process), &next_cycle_to_die, &cycle_to_die);
	//	ft_printf("cycle: %d\n", arn->nb_cycle);
		run_processes(arn);
		print_test(*arn);
		if (dump == arn->nb_cycle)
			return (dump_mem(*arn));
		arn->nb_cycle++;
	}
	find_winner(arn);
}
