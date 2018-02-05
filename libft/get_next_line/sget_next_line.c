/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sget_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 22:41:59 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/24 23:17:08 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				sget_next_char(const int fd, char **line, char c)
{
	static char		buff[BUFF_SIZE + 1];
	int				ret;
	int				endl;
	int				idx;

	if (!line || !(*line = ft_strnew(BUFF_SIZE)) || BUFF_SIZE < 1)
		return (-1);
	while (1)
	{
		if (!*buff)
			ft_bzero(buff, BUFF_SIZE + 1);
		if (!*buff && (ret = read(fd, buff, BUFF_SIZE)) < 0)
			return (-1);
		if (!ret && **line)
			return (1);
		if (!ret && !*buff)
			return (0);
		idx = ft_strchrindex(buff, c);
		if ((endl = ft_charinset(c, buff)) < 0 ||
				!(*line = ft_strnjoinclr(*line, buff, idx, 1)))
			return (-1);
		ft_strcpy((char*)buff, &(buff[(buff[idx] == c) ? (idx + 1) : idx]));
		if (endl)
			return (1);
	}
}

int				sget_next_line(const int fd, char **line)
{
	return (sget_next_char(fd, line, '\n'));
}
