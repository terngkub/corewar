/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <pnardozi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 17:34:03 by pnardozi          #+#    #+#             */
/*   Updated: 2018/03/02 17:51:37 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	put_win(t_visu v, t_arena *arn, int win)
{
	wattron(v.info, A_UNDERLINE | COLOR_PAIR(7));
	mvwprintw(v.info, 2, 2, "The winner is %s !",\
			arn->players[win - 1].name);
	wattroff(v.info, A_UNDERLINE);
	wattron(v.info, COLOR_PAIR(1));
	wattron(v.info, COLOR_PAIR(14));
	mvwprintw(v.info, 4, 2, "%7s", "DONE");
	wattron(v.info, COLOR_PAIR(1));
}

void	put_onebyone(t_visu v)
{
	wattron(v.info, COLOR_PAIR(14));
	mvwprintw(v.info, 4, 2, "%7s", "1 BY 1");
	wattron(v.info, COLOR_PAIR(1));
}

void	put_pause(t_visu v)
{
	wattron(v.info, COLOR_PAIR(14));
	mvwprintw(v.info, 4, 2, "%7s", "PAUSE");
	wattron(v.info, COLOR_PAIR(1));
}

void	put_running(t_visu v)
{
	wattron(v.info, COLOR_PAIR(14));
	mvwprintw(v.info, 4, 2, "RUNNING");
	wattron(v.info, COLOR_PAIR(1));
}
