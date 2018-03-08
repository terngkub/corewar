/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <pnardozi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 12:07:18 by pnardozi          #+#    #+#             */
/*   Updated: 2018/03/02 17:03:04 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	f_p(char *byte, char mem)
{
	unsigned char	tmp;
	char			base[17];

	ft_memcpy((char*)base, "0123456789abcdef\0", 17);
	tmp = (unsigned char)mem;
	byte[0] = base[tmp / 16];
	byte[1] = base[tmp % 16];
}

void	put_man(t_visu *v)
{
	mvwprintw(v->man, 1, 1, "ESC : QUIT");
	mvwprintw(v->man, 2, 1, "SPACE : RUN/PAUSE");
	mvwprintw(v->man, 3, 1, "D : CYCLE BY CYCLE");
	wrefresh(v->man);
}

int		free_visu(t_visu *v)
{
	clear();
	delwin(v->arena);
	delwin(v->info);
	delwin(v->background);
	delwin(v->man);
	endwin();
	return (0);
}

void	set_color(t_visu v, char c)
{
	if (c == 1)
		wattron(v.arena, COLOR_PAIR(1));
	if (c == 2)
		wattron(v.arena, COLOR_PAIR(3));
	if (c == 3)
		wattron(v.arena, COLOR_PAIR(4));
	if (c == 4)
		wattron(v.arena, COLOR_PAIR(5));
	if (c == 5)
		wattron(v.arena, COLOR_PAIR(6));
	if (c == -1)
		wattron(v.arena, COLOR_PAIR(10));
	if (c == -2)
		wattron(v.arena, COLOR_PAIR(11));
	if (c == -3)
		wattron(v.arena, COLOR_PAIR(12));
	if (c == -4)
		wattron(v.arena, COLOR_PAIR(13));
	if (c == -5)
		wattron(v.arena, COLOR_PAIR(14));
}

void	put_winner(t_arena *arn, t_visu *v)
{
	int		i;
	int		winner;

	i = arn->nb_players - 1;
	winner = i + 1;
	while (i >= 0)
	{
		if (arn->players[i].number == arn->winner)
			winner = i + 1;
		i--;
	}
	put_info(*v, arn, winner, 3);
}
