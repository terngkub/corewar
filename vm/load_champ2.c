/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_champ2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:17:21 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/17 13:42:16 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_magic(char *header, char *l)
{
	unsigned int	magic;

	magic = x_char_to_int(&header[0], 4);
	if (magic != COREWAR_EXEC_MAGIC)
	{
		ft_strdel(&header);
		ft_strdel(&l);
		return (0);
	}
	return (1);
}

int		check_champ_size(int fd, char *header, char *l)
{
	unsigned int	size;
	unsigned int	i;

	i = 0;
	size = x_char_to_int(&header[PROG_NAME_LENGTH + 8], 4);
	while (read(fd, l, 1) > 0)
	{
		i++;
		if (i > size + 10)
			break ;
	}
	if (i == size)
		return (1);
	ft_strdel(&header);
	ft_strdel(&l);
	return (0);
}

int		get_header(int fd, char *l, char *header)
{
	int		i;

	i = 0;
	while (i < PROG_NAME_LENGTH + COMMENT_LENGTH + 16)
	{
		if (read(fd, l, 1) <= 0)
		{
			ft_strdel(&header);
			ft_strdel(&l);
			return (0);
		}
		header[i] = l[0];
		i++;
	}
	return (1);
}

int		check_header(int fd, char *l)
{
	char	*header;

	if (!(header = ft_strnew(PROG_NAME_LENGTH + COMMENT_LENGTH + 16)))
		exit(0);
	if (!(get_header(fd, l, header)))
		return (0);
	if (!(check_magic(header, l)))
		return (0);
	if (!(check_champ_size(fd, header, l)))
		return (0);
	ft_strdel(&header);
	lseek(fd, 0, SEEK_SET);
	return (1);
}
