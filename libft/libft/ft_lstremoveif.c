/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremoveif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 21:59:28 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/25 20:41:31 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstremoveif(t_list **begin_list, void *content_ref,
					int (*cmp)(), size_t size)
{
	t_list		*tmp;
	t_list		*curr;

	while (*begin_list && !cmp((*begin_list)->content, content_ref,
			size))
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(tmp);
	}
	curr = *begin_list;
	while (curr && curr->next)
	{
		if (!cmp((curr->next->content), content_ref, size))
		{
			tmp = curr->next;
			curr->next = tmp->next;
			free(tmp);
		}
		if (curr->next)
			curr = curr->next;
	}
}
