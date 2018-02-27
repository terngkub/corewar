/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:40:33 by arobion           #+#    #+#             */
/*   Updated: 2018/02/27 17:08:28 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		get_number2(char **argv, char **flag, int *j, t_norme opt)
{
	*flag = ft_strndup(argv[*j], 0, 2);
	if (ft_strcmp(*flag, "-n ") == 0)
	{
		free(*flag);
		*flag = ft_strndup(argv[*j], 3, opt.len);
		ft_printf("%s\n", *flag);
		opt.nb = ft_long_atoi(*flag);
		*j += 1;
		free(*flag);
	}
	else
		free(*flag);
}

int			get_number(char **argv, int *j)
{
	char		*flag;
	t_norme		opt;

	opt.nb = 0;
	opt.len = ft_strlen(argv[*j]);
	if (opt.len > 2)
		get_number2(argv, &flag, j, opt);
	else if (opt.len == 2)
	{
		flag = ft_strdup(argv[*j]);
		if (ft_strcmp(flag, "-n") == 0)
		{
			free(flag);
			*j += 1;
			flag = ft_strdup(argv[*j]);
			opt.nb = ft_long_atoi(flag);
			*j += 1;
			free(flag);
		}
		else
			free(flag);
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

int			ft_is_in(int j, int *tab, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (tab[i] == j)
			return (1);
		i++;
	}
	return (0);
}

int			choose_player_number(t_player *players, int nb_players)
{
	int		i;
	int		*tab;
	int		j;

	j = 1;
	if (!(tab = (int*)malloc(sizeof(int) * nb_players)))
		exit(0);
	i = 0;
	while (i < nb_players)
	{
		tab[i] = players[i].number;
		i++;
	}
	i = 0;
	while (ft_is_in(j, tab, nb_players) == 1)
		j++;
	free(tab);
	return (j);
}

int			verif_unicity_of_player(t_player *players, int nb_players)
{
	int		i;
	int		j;

	i = 0;
	while (i < nb_players - 1)
	{
		j = i + 1;
		while (j < nb_players)
		{
			if (players[j].number == players[i].number)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int			reaffect_number(t_player *players, int nb_players)
{
	int		i;

	i = 0;
	while (i < nb_players)
	{
		if (players[i].number == 0)
			players[i].number = choose_player_number(players, nb_players);
		i++;
	}
	if (!(verif_unicity_of_player(players, nb_players)))
		return (0);
	return (1);
}

int			init_players(t_player *players, int nb_players,\
		char **argv, int start)
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
	if (!(reaffect_number(players, nb_players)))
		return (0);
	return (1);
}
