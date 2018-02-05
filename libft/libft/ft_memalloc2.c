/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 16:54:05 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/30 16:01:07 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free2(void **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	**ft_memalloc2(size_t si1, size_t si2, size_t size)
{
	void		**t;
	size_t		i;

	i = -1;
	if (si1 < 1 || si2 < 1)
		return (NULL);
	if (!(t = (void**)ft_memalloc((si1 + 1) * sizeof(void*))))
		return (NULL);
	while (++i < size)
		if (!(t[i] = (void*)ft_memalloc(si2 * size)))
			return (NULL);
	return (t);
}
