/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_labels_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 19:56:07 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/09 14:50:23 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	print_label(t_label *label)
{
	ft_printf("name %s\n", label->name);
	ft_printf("addr %d\n", label->addr);
}

void	print_labels_list(t_list *list)
{
	ft_printf("\n-----Labels-----\n\n");
	while (list)
	{
		print_label((t_label *)list->content);
		list = list->next;
	}
}
