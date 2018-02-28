/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichages.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 13:56:48 by arobion           #+#    #+#             */
/*   Updated: 2018/02/28 12:19:36 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		print_no_file(char *str)
{
	ft_printf("Can't read source file %s\n", str);
	return (0);
}

int		write_usage(void)
{
	ft_printf("Usage: ./corewar [-dump N] [-n N] <champion1.cor> <...>\n");
	return (0);
}

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
				ft_printf("%#.4x : ", i + 1);
		}
		i++;
	}
	freeall(&arn);
}
