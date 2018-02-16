/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichages.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 13:56:48 by arobion           #+#    #+#             */
/*   Updated: 2018/02/16 14:55:47 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdio.h>

void	dump_mem(t_arena arn)
{
	int		i;

	i = 0;
	if (MEM_SIZE != 0)
		write(1, "0x0000 : ", 9);
	while (i < MEM_SIZE)
	{
		ft_printf("%.2hhx ", arn.mem[i]);
		if ((i + 1) % 64 == 0 && i != 0)
		{
			ft_printf("\n");
			if (i + 1 < MEM_SIZE)
				dprintf(1, "%#.4x : ", i + 1);
		}
		i++;
	}
}

void	print_registry(char **regs)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		ft_printf("Registry %d: %.2hhx %.2hhx %.2hhx %2.hhx\n", i, regs[i][0], regs[i][1], regs[i][2], regs[i][3]);
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

	lst = *begin_list;
	while (lst)
	{
		ft_printf("playernumber = %d\n", x_char_to_int(lst->regs[0], REG_SIZE));
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
		ft_printf("player number = %d\n", players[i].number);
		ft_printf("name player %d = %s\ncomment player %d = %s\nnb_live player %d = %d\nlast_live player %d = %d\n\n", i + 1, players[i].name\
				, i + 1, players[i].comment, i + 1, players[i].nb_live, i + 1\
				, players[i].last_live);
		i++;
	}
}

void	print_arena(t_arena arn)
{
	ft_printf("nb_cycle = %d\nnb_checks = %d\nnb_players = %d\n\n",\
			arn.nb_cycle, arn.nb_checks, arn.nb_players);
	print_players(arn.players, arn);
	print_process(&(arn.process));
}
