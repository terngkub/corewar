/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:38:23 by arobion           #+#    #+#             */
/*   Updated: 2018/03/17 16:01:16 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		weigh_champ(char *str)
{
	int		fd;
	char	*l;
	int		i;

	i = 0;
	if (!(l = ft_strnew(1)))
		exit(0);
	if ((fd = open(str, O_RDONLY)) < 0)
		exit(0);
	while (read(fd, l, 1))
		i++;
	ft_strdel(&l);
	close(fd);
	return (i - (PROG_NAME_LENGTH + COMMENT_LENGTH + 16));
}

void	introduce_players(t_arena arn, char **argv, int start, int argc)
{
	int		i;
	int		index;

	index = start;
	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < arn.nb_players)
	{
		check_number(argc, argv, &index);
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n"\
				, arn.players[i].number, weigh_champ(argv[index]),\
				arn.players[i].name, arn.players[i].comment);
		i++;
		index++;
	}
}

void	free_players(t_player *players, int nb_players)
{
	int		i;

	i = 0;
	while (i < nb_players)
	{
		ft_strdel(&players[i].name);
		ft_strdel(&players[i].comment);
		i++;
	}
	free(players);
}

int		init_arena(t_arena *arn, int nb_players, char **argv, t_norme opt)
{
	(*arn).nb_cycle = 0;
	(*arn).nb_players = nb_players;
	(*arn).nb_checks = 0;
	arn->lives = 0;
	if (!((*arn).players = (t_player*)malloc(sizeof(t_player) * nb_players)))
		exit(0);
	if (!(init_players((*arn).players, nb_players, argv, opt.i)))
	{
		free_players((*arn).players, nb_players);
		return (0);
	}
	(*arn).process = NULL;
	init_process(*arn, &(arn->process));
	introduce_players(*arn, argv, opt.i, opt.argc);
	return (1);
}
