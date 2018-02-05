/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 18:39:12 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/05 19:07:03 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	read_input(char *file_name)
{
	int		fd;
	char	*str;

	fd = open(file_name);
	while (get_next_line(fd, str) > 0)
	{
		ft_printf("test\n");
	}
	close(fd);
}

int		main(void)
{
	if (argc < 2)
	{
		ft_printf("ERROR");
		return (1);
	}
	read_input(argv[argc - 1]);
	return (0);
}
