/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 22:27:37 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/25 14:28:02 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_player	*find_player(t_arena *arn, int number)
{
	int		player_no;
	int		i;

	i = 0;
	while (i < arn->nb_players)
	{
		player_no = arn->players[i].number;
		if (player_no == number)
			return (&arn->players[i]);
		i++;
	}
	return (NULL);
}

static int		get_player_number(t_arena *arn, t_process *process)
{
	char		*str;
	int			i;
	int			number;

	if (!(str = ft_strnew(4)))
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < 4)
		str[i] = arn->mem[(process->pc + i + 1) % MEM_SIZE];
	number = -hex_to_dec(str, 4);
	free(str);
	return (number);
}

void			live(t_arena *arn, t_process *process)
{
	int			number;
	t_player	*player;

	number = get_player_number(arn, process);
	process->alive = 1;
	process->pc = (process->pc + 5) % MEM_SIZE;
	arn->lives += 1;
	arn->winner = number;
	if (!(player = find_player(arn, number)))
		return ;
	player->nb_live++;
	player->last_live = arn->nb_cycle;
}
