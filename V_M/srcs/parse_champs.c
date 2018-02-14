/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:32:42 by arobion           #+#    #+#             */
/*   Updated: 2018/02/14 20:05:32 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		write_usage(void)
{
	ft_printf("Usage: ./corewar <champion1.cor> <...>\n");
	return (0);
}

int		ft_checkname(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	i -= 4;
	if (str[i++] != '.')
		return (0);
	if (str[i++] != 'c')
		return (0);
	if (str[i++] != 'o')
		return (0);
	if (str[i++] != 'r')
		return (0);
	return (1);
}

int		parse_champs(int argc, char **argv)
{
	int		i;

	i = 1;
	if (argc - 1 > MAX_PLAYERS)
	{
		ft_printf("Too many champions\n");
		return (0);
	}
	if (argc <= 1)
		return (write_usage());
	while (i < argc)
	{
		if (ft_checkname(argv[i]) == 0)
		{
			ft_printf("Error: File %s is too small to be a champion\n"\
					, argv[i]);
			return (0);
		}
		i++;
	}
	return (argc - 1);
}
