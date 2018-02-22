/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 22:27:37 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/22 18:17:17 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		live(t_arena *arn, t_process *process)
{
	char		*str;
	int			i;
	int			number;
	t_player	*player;

	if (!(str = ft_strnew(4)))
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < 4)
		str[i] = arn->mem[(process->pc + i + 1) % MEM_SIZE];
	number = hex_to_dec(str, 4);
	free(str);
	//number = hex_to_dec(&arn->mem[(process->pc + 1) % MEM_SIZE], 4);
	number = -number;
	process->alive = 1;
	process->pc = (process->pc + 5) % MEM_SIZE;
	arn->lives += 1;
	arn->winner = number;
	if (!(player = find_player(arn, number)))
		return ;
	player->nb_live++;
	player->last_live = arn->nb_cycle;
}
