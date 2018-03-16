/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:40:33 by arobion           #+#    #+#             */
/*   Updated: 2018/03/16 20:20:57 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
	ft_memdel((void**)&tab);
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
