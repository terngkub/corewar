/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:02:09 by arobion           #+#    #+#             */
/*   Updated: 2018/02/27 16:06:16 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_registry(char **regs)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		ft_printf("Registry %d: %.2hhx %.2hhx %.2hhx %2.hhx\n", i + 1,\
				regs[i][0], regs[i][1], regs[i][2], regs[i][3]);
		i++;
	}
}

void	print_mem(char *mem, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		ft_printf("%.2hhx ", mem[i]);
		if ((i + 1) % 16 == 0 && i != 0)
			ft_printf(" \n");
		else if ((i + 1) % 8 == 0 && i != 0)
			ft_printf(" ");
		i++;
	}
}

void	print_process(t_process **begin_list)
{
	t_process *lst;
	int			i;

	i = 1;
	lst = *begin_list;
	while (lst)
	{
		ft_printf("process number %d : \n", i++);
		ft_printf("color = %d\n", lst->color);
		print_registry(lst->regs);
		ft_printf("opc = %.2x\ncycle_to_wait = %d\npc = %d\ncarry = %d\n\n",\
				lst->opc, lst->cycle_to_wait, lst->pc, lst->carry);
		lst = lst->next;
	}
}

void	print_players(t_player *players, t_arena arn)
{
	int		i;

	i = 0;
	while (i < arn.nb_players)
	{
		ft_printf("player number %d\n", players[i].number);
		ft_printf("name player %d = %s\nnb_live player %d = %d\nlast_live player %d = %d\n\n", i + 1, players[i].name\
				, i + 1, i + 1, players[i].nb_live, i + 1\
				, players[i].last_live);
		i++;
	}
}

void	print_arena(t_arena arn)
{
	ft_printf("nb_cycle = %d\nnb_checks = %d\nnb_players = %d\n\n",\
			arn.nb_cycle, arn.nb_checks, arn.nb_players);
	print_mem(arn.color, MEM_SIZE);
	print_players(arn.players, arn);
	print_process(&(arn.process));
}

void		print_test(t_arena arn)
{
	if (arn.nb_cycle == 8000)
	{
		ft_printf("\n\n YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYy\n");

		print_arena(arn);
	}
}

void	print_proc_test(t_process *process, int i, t_arena *arn)
{
	int			j;

	i += 0;
	j = 0;
	(void)arn;
	if (process->opc != 0 && process->op)
	{
		ft_printf("cycle %4d\tcarry %d\t pc %d\t%d\t", arn->nb_cycle, process->carry, process->pc, process->opc);
		j = 0;
		while (j < 10)
		{
			ft_printf(" %02hhx", arn->mem[(process->pc + j) % MEM_SIZE]);
			j++;
		}
		ft_printf("\n");
	}
}
