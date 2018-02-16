/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int2dump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 21:30:41 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/27 17:03:19 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_int2dump(int **array)
{
	int		i;

	i = -1;
	if (!array || !*array)
		return ;
	while (array[++i])
	{
		ft_putstr("[");
		ft_putnbr(*array[i]);
		ft_putstr("] ");
	}
	/*while (++i < size + 1)
	{
		ft_putstr("[");
		ft_putnbr(*array[i]);
		ft_putstr("] ");
	}*/
	ft_putstr("\n");
}
