/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:38:23 by arobion           #+#    #+#             */
/*   Updated: 2018/02/27 16:24:56 by arobion          ###   ########.fr       */
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
	fd = open(str, O_RDONLY);
	while (read(fd, l, 1))
		i++;
	free(l);
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

int		init_arena(t_arena *arn, int nb_players, char **argv, int i, int argc)
{
	(*arn).nb_cycle = 0;
	(*arn).nb_players = nb_players;
	(*arn).nb_checks = 0;
	arn->lives = 0;
	if (!((*arn).players = (t_player*)malloc(sizeof(t_player) * nb_players)))
		exit(0);
	if (!(init_players((*arn).players, nb_players, argv, i)))
		return (0);
	(*arn).process = NULL;
	init_process(*arn, &(arn->process));
	introduce_players(*arn, argv, i, argc);
	return (1);
}
