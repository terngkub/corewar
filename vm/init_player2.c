/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:07:55 by arobion           #+#    #+#             */
/*   Updated: 2018/03/17 16:01:47 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		get_number2(char **argv, char **flag, int *j, t_norme *opt)
{
	if (!(*flag = ft_strndup(argv[*j], 0, 2)))
		exit(0);
	if (ft_strcmp(*flag, "-n ") == 0)
	{
		ft_strdel(flag);
		if (!(*flag = ft_strndup(argv[*j], 3, (*opt).len)))
			exit(0);
		(*opt).nb = ft_long_atoi(*flag);
		*j += 1;
		ft_strdel(flag);
	}
	else
		ft_strdel(flag);
}

int			get_number(char **argv, int *j)
{
	char		*flag;
	t_norme		opt;

	opt.nb = 0;
	opt.len = ft_strlen(argv[*j]);
	if (opt.len > 2)
		get_number2(argv, &flag, j, &opt);
	else if (opt.len == 2)
	{
		if (!(flag = ft_strdup(argv[*j])))
			exit(0);
		if (ft_strcmp(flag, "-n") == 0)
		{
			ft_strdel(&flag);
			*j += 1;
			if (!(flag = ft_strdup(argv[*j])))
				exit(0);
			opt.nb = ft_long_atoi(flag);
			*j += 1;
			ft_strdel(&flag);
		}
		else
			ft_strdel(&flag);
	}
	return (opt.nb);
}

void		create_name(int fd, char *name, char *l)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < 4)
		read(fd, l, 1);
	while (i < 4 + PROG_NAME_LENGTH)
	{
		read(fd, l, 1);
		name[j++] = l[0];
		i++;
	}
}

void		create_comment(int fd, char *comment, char *l)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < 8)
		read(fd, l, 1);
	while (i < 8 + COMMENT_LENGTH)
	{
		read(fd, l, 1);
		comment[j++] = l[0];
		i++;
	}
}

t_player	create_one_player(char *champ, int number)
{
	t_player	player;
	int			fd;
	char		*l;

	if (!(l = ft_strnew(1)))
		exit(0);
	if (!(player.name = ft_strnew(PROG_NAME_LENGTH)))
		exit(0);
	if (!(player.comment = ft_strnew(COMMENT_LENGTH)))
		exit(0);
	if ((fd = open(champ, O_RDONLY)) < 0)
		exit(0);
	create_name(fd, player.name, l);
	create_comment(fd, player.comment, l);
	player.number = number;
	player.nb_live = 0;
	player.last_live = 0;
	ft_strdel(&l);
	close(fd);
	return (player);
}
