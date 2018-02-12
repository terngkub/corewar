/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:25:47 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/12 19:35:52 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	print_inst_list(t_list *list)
{
	t_inst	*inst;
	int		i;

	ft_printf("\n-----Instructions-----\n\n");
	while (list)
	{
		inst = (t_inst *)list->content;
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
		ft_printf("\n");
		list = list->next;
	}
}

void	print_labels_list(t_list *list)
{
	t_label	*label;

	ft_printf("\n-----Labels-----\n\n");
	while (list)
	{
		label = (t_label *)list->content;
		ft_printf("name %s\n", label->name);
		ft_printf("addr %d\n", label->addr);
		ft_printf("\n");
		list = list->next;
	}
}
