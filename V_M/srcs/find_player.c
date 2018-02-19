/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:28:32 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/19 21:10:04 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_player	*find_player(t_arena *arn, int number)
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
