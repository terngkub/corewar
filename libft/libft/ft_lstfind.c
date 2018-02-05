/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 21:55:24 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/25 21:15:00 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstfind(t_list *begin_list, void *data_ref, int (*cmp)(),
		size_t size)
{
	t_list		*tmp;

	if (!begin_list || !data_ref || !cmp)
		return (begin_list);
	tmp = begin_list;
	while (tmp)
	{
		if ((*cmp)(tmp->content, data_ref, size) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}
