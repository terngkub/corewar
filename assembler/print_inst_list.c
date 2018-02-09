/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_inst_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 19:42:40 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/09 14:45:14 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	print_inst(t_inst *inst)
{
	int 	i;

	ft_printf("opcode %d\n", (int)inst->opcode);
	ft_printf("ocp %d\n", (int)inst->ocp);
	ft_printf("param_byte %d\n", (int)inst->param_byte);
	ft_printf("addr %d\n", (int)inst->addr);
	ft_printf("len %d\n", (int)inst->len);
	ft_printf("param_num %d\n", (int)inst->param_num);
	i = 0;
	while (i < (int)inst->param_num)
	{
		ft_printf("%d %s\n", i, inst->param_arr[i]);
		i++;
	}
}

void		print_inst_list(t_list *list)
{
	ft_printf("\n-----Instructions-----\n\n");
	while (list)
	{
		print_inst((t_inst *)list->content);
		ft_printf("\n");
		list = list->next;
	}
}
