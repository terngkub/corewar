/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 21:52:40 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/25 21:06:56 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_eldel(void *content, size_t content_size)
{
	(void)content_size;
	(void)content;
}

void	ft_elemdel(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
	content = NULL;
}

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*tmp;

	if (!alst || !del)
		return ;
	while (*alst)
	{
		tmp = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = NULL;
		*alst = tmp;
	}
}
