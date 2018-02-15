/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:40:33 by arobion           #+#    #+#             */
/*   Updated: 2018/02/15 17:49:07 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
	fd = open(champ, O_RDONLY);
	create_name(fd, player.name, l);
	create_comment(fd, player.comment, l);
	player.number = number;
	player.nb_live = 0;
	player.last_live = 0;
	free(l);
	close(fd);
	return (player);
}

void		init_players(t_player *players, int nb_players, char **argv, int start)
{
	int		i;

	i = 0;
	while (i < nb_players)
	{
		players[i] = create_one_player(argv[start], i + 1);
		start++;
		i++;
	}
}
