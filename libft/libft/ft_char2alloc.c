/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char2alloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 15:17:54 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/16 15:20:21 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_char2alloc(size_t size, size_t len)
{
	char		**t;
	size_t		i;

	i = -1;
	if (size < 1 || len < 1)
		return (NULL);
	if (!(t = (char**)ft_memalloc((size + 1) * sizeof(char*))))
		return (NULL);
	while (++i < size)
		if (!(t[i] = (char*)ft_memalloc((len + 1) * sizeof(char))))
			return (NULL);
	return (t);
}
