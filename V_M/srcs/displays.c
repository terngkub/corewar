/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichages.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 13:56:48 by arobion           #+#    #+#             */
/*   Updated: 2018/02/14 15:33:09 by arobion          ###   ########.fr       */
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
		if ((i + 1)% 16 == 0 && i != 0)
			ft_printf(" \n");
		else if ((i + 1) % 8 == 0 && i != 0)
			ft_printf(" ");
		i++;
	}
}
/*
void	print_process(t_process *lst)
{
	while (lst)
	{
		print_mem(lst->regs, REG_SIZE * REG_NUMBER);
		ft_printf("opc = %d\ncycle_to_wait = %d\npc = %d\ncarry = %d\n", lst->opc, lst->cycle_to_wait, lst->pc, lst->carry);
	   lst = lst->next;
	}
}
*/
void	print_arena(t_arena arn)
{
	ft_printf("nb_cycle = %d\nnb_checks = %d\n", arn.nb_cycle, arn.nb_checks);
	ft_printf("\n");
}
