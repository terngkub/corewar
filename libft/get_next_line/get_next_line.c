/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 14:04:29 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/29 20:45:29 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void			ft_gnlremovefd(t_gnl **begin_gnl, int fd)
{
	t_gnl	*tmp;
	t_gnl	*curr;

	while (*begin_gnl && (*begin_gnl)->fd == fd)
	{
		tmp = *begin_gnl;
		*begin_gnl = (*begin_gnl)->next;
		free(tmp);
	}
	curr = *begin_gnl;
	while (curr && curr->next)
	{
		if (curr->next->fd == fd)
		{
			tmp = curr->next;
			curr->next = tmp->next;
			free(tmp);
		}
		if (curr->next)
			curr = curr->next;
	}
}

void			ft_gnlpushfront(t_gnl **begin_gnl, int fd)
{
	t_gnl		*t;

	if (!begin_gnl)
		return ;
	if ((t = (t_gnl*)malloc(sizeof(t_gnl))) == NULL)
		return ;
	(t)->fd = fd;
	(t)->next = NULL;
	ft_bzero((t)->buff, BUFF_SIZE + 1);
	if (*begin_gnl)
	{
		t->next = (*begin_gnl);
		(*begin_gnl) = t;
	}
	else
		(*begin_gnl) = t;
}

t_gnl			*ft_gnlfindfd(t_gnl *begin_list, int fd)
{
	t_gnl		*tmp;

	if (!begin_list)
		return (begin_list);
	tmp = begin_list;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

int				get_next_char(const int fd, char **line, char *buff, char c)
{
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

int				get_next_line(const int fd, char **line)
{
	static t_gnl		*g;
	t_gnl				*tmp;
	int					ret;

	if (fd < 0)
		return (-1);
	if (!(tmp = ft_gnlfindfd(g, fd)))
	{
		ft_gnlpushfront(&g, fd);
		tmp = ft_gnlfindfd(g, fd);
	}
	if ((ret = get_next_char(fd, line, tmp->buff, '\n')) == 0)
		ft_gnlremovefd(&g, fd);
	return (ret);
}
