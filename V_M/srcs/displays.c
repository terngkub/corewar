/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichages.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 13:56:48 by arobion           #+#    #+#             */
/*   Updated: 2018/02/27 16:06:16 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdio.h>

void	dump_mem(t_arena arn)
{
	int		i;

	i = 0;
	if (MEM_SIZE != 0)
		write(1, "0x0000 : ", 9);
	while (i < MEM_SIZE)
	{
		ft_printf("%.2hhx ", arn.mem[i]);
		if ((i + 1) % 64 == 0 && i != 0)
		{
			ft_printf("\n");
			if (i + 1 < MEM_SIZE)
				dprintf(1, "%#.4x : ", i + 1);
		}
		i++;
	}
}
