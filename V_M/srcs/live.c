/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 22:27:37 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/15 14:37:31 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		live(t_arena *arn, t_process *process)
{
	int			number;
	t_player	*player;

	number = hex_to_dec(&arn->mem[process->pc + 1], 4);
	process->alive = 1;
	process->pc += 5;
	if (!(player = find_player(arn, number)))
		return ;
	player->nb_live++;
	player->last_live = arn->nb_cycle;
}
