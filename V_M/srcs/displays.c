/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichages.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 13:56:48 by arobion           #+#    #+#             */
/*   Updated: 2018/02/15 12:13:26 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
