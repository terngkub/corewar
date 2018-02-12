/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_integrity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 20:13:10 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/12 20:41:48 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	check_each_label(t_inst *inst, t_list *labels_list, int i)
{
	int			j;
	int			found;
	t_label		*label;

	j = ft_strchr(inst->param_arr[i], '%') ? 2 : 1;
	found = 0;
	while (labels_list)
	{
		label = (t_label *)labels_list->content;
		if (ft_strcmp(&inst->param_arr[i][j], label->name) == 0)
		{
			found = 1;
			break ;
		}
		labels_list = labels_list->next;
	}
	if (found == 0)
		ft_error("can't find referenced label of the parameters");
}

static void	check_label(t_list *inst_list, t_list *labels_list)
{
	t_inst		*inst;
	int			i;

	while (inst_list)
	{
		inst = (t_inst *)inst_list->content;
		i = 0;
		while (i < inst->param_num)
		{
			if (ft_strchr(inst->param_arr[i], ':'))
				check_each_label(inst, labels_list, i);
			i++;
		}
		inst_list = inst_list->next;
	}
}

int			check_integrity(t_champ *champ, t_check *check)
{
	if (check->name == 0)
		return (ft_error_return("champion has no name", 0));
	if (check->comment == 0)
		return (ft_error_return("champion has no comment", 0));
	if (!champ->inst)
		return (ft_error_return("champion has no instruction", 0));
	check_label(champ->inst, champ->labels);
	return (1);
}
