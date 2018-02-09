/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_labels_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 19:56:07 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/08 19:57:38 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	print_labels_list(t_list *list)
{
	ft_printf("\n-----Labels-----\n\n");
	while (list)
	{
		ft_printf("%s\n", (char *)list->content);
		list = list->next;
	}
}
