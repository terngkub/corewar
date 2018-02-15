/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 22:27:37 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/15 13:43:43 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			hex_to_dec(char *str, int len)
{
	int		sum;

	sum = 0;
	while (len--)
		sum = sum * 256 + (unsigned char)*str++;
	return (sum);
}

t_player	*find_player(t_arena *arena, int number)
{
	int		player_no;
	int		i;

	i = 0;
	while (i < arena->nb_players)
	{
		player_no = arena->players[i].number;
		if (player_no == number)
			return (&arena->players[i]);
		i++;
	}
	return (NULL);
}

void		live(t_arena *arena, t_process *process, int cycle)
{
	int			number;
	t_player	*player;

	process->alive = 1;
	number = hex_to_dec(&arena->mem[process->pc + 1], 4);
	if (!(player = find_player(arena, number)))
		return ;
	player->nb_live++;
	player->last_live = cycle;
}
