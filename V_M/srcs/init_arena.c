/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:38:23 by arobion           #+#    #+#             */
/*   Updated: 2018/02/15 16:09:16 by arobion          ###   ########.fr       */
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

void	introduce_players(t_arena arn, char **argv)
{
	int		i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < arn.nb_players)
	{
		ft_printf("* Player %d, wheighing %d bytes, \"%s\" (\"%s\") !\n"\
				, i + 1, weigh_champ(argv[i + 1]), arn.players[i].name\
				, arn.players[i].comment);
		i++;
	}
}

void	init_arena(t_arena *arn, int nb_players, char **argv)
{
	(*arn).nb_cycle = 0;
	(*arn).nb_players = nb_players;
	(*arn).nb_checks = 0;
	if (!((*arn).players = (t_player*)malloc(sizeof(t_player) * nb_players)))
		exit(0);
	init_players((*arn).players, nb_players, argv);
	(*arn).process = NULL;
	init_process(*arn, &(arn->process));
	introduce_players(*arn, argv);
}
