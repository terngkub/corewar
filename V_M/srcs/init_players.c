/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:40:33 by arobion           #+#    #+#             */
/*   Updated: 2018/02/16 15:56:40 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_number(char **argv, int *j)
{
	size_t		len;
	char		*flag;
	long long	nb;

	nb = 0;
	len	 = ft_strlen(argv[*j]);
	if (len > 2)
	{
		flag = ft_strndup(argv[*j], 0, 2);
		if (ft_strcmp(flag, "-n ") == 0)
		{
			free(flag);
			flag = ft_strndup(argv[*j], 3, len);
			ft_printf("%s\n", flag);
			nb = ft_long_atoi(flag);
			*j += 1;
			free(flag);
		}
		else
			free(flag);
	}
	else if (len == 2)
	{
		flag = ft_strdup(argv[*j]);
		if (ft_strcmp(flag, "-n") == 0)
		{
				free(flag);
				*j += 1;
				flag = ft_strdup(argv[*j]);
				nb = ft_long_atoi(flag);
				*j += 1;
				free(flag);
		}
		else
			free(flag);
	}
	return (nb);
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
	int		nb_for_player;
	int		index;

	i = 0;
	index = start;
	while (i < nb_players)
	{
		nb_for_player = 0;
		nb_for_player = get_number(argv, &index);
		players[i] = create_one_player(argv[index], nb_for_player);
		index++;
		i++;
	}
}
