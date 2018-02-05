/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int2alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 15:16:45 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/16 15:32:38 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		**ft_int2alloc(size_t size, size_t len)
{
	int			**t;
	size_t		i;

	i = -1;
	if (size < 1 || len < 1)
		return (NULL);
	if (!(t = (int**)ft_memalloc((size + 1) * sizeof(int*))))
		return (NULL);
	while (++i < size)
		if (!(t[i] = (int*)ft_memalloc(len * sizeof(int))))
			return (NULL);
	return (t);
}
