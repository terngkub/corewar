/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <pnardozi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 13:43:32 by pnardozi          #+#    #+#             */
/*   Updated: 2018/03/08 15:51:28 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			put_info2(t_visu v, t_arena *arn, int *u, int i)
{
	wattron(v.info, COLOR_PAIR(arn->players[i].number + 2));
	mvwprintw(v.info, *u, 2, "Player %3d : %10s",\
			arn->players[i].number, arn->players[i].name);
	wattron(v.info, COLOR_PAIR(1));
	mvwprintw(v.info, *u + 1, 3, "Last live : %5d",\
			arn->players[i].last_live);
	mvwprintw(v.info, *u + 2, 3, "Lives in current period : %5d",\
			arn->players[i].nb_live);
	*u += 5;
}

void			put_info(t_visu v, t_arena *arn, int win, int run)
{
	int		i;
	int		u;

	u = 16;
	i = -1;
	if (win)
		put_win(v, arn, win);
	if (run == 1)
		put_onebyone(v);
	else if (run == 2)
		put_pause(v);
	else if (run != 3)
		put_running(v);
	if (run == 3)
		v.cycle_to_die = 0;
	mvwprintw(v.info, 6, 2, "Cycles : %5d", arn->nb_cycle);
	mvwprintw(v.info, 8, 2, "Processes : %5d", v.proc);
	mvwprintw(v.info, 10, 2, "CYCLE TO DIE : %5d", v.cycle_to_die);
	mvwprintw(v.info, 12, 2, "CYCLE_DELTA : %5d", CYCLE_DELTA);
	mvwprintw(v.info, 14, 2, "NBR_LIVE : %5d", NBR_LIVE);
	mvwprintw(v.info, 16, 2, "MAX_CHECKS : %5d", MAX_CHECKS);
	while (++i < arn->nb_players)
		put_info2(v, arn, &u, i);
	wrefresh(v.info);
}

static int		init_visu(t_visu *v)
{
	int			c;

	c = 0;
	set_colorx();
	v->cycle_to_die = CYCLE_TO_DIE;
	v->next_cycle_to_die = CYCLE_TO_DIE;
	v->arena = subwin(stdscr, 66, 260, 1, 5);
	v->info = subwin(stdscr, 66, 90, 1, COLS - 95);
	v->background = subwin(stdscr, LINES, COLS, 0, 0);
	v->man = subwin(stdscr, 5, 25, 70, 5);
	wattron(v->background, COLOR_PAIR(1));
	box(v->background, ACS_VLINE, ACS_HLINE);
	wattron(v->arena, COLOR_PAIR(1));
	wattron(v->info, COLOR_PAIR(1));
	wattron(v->man, COLOR_PAIR(1));
	wattron(v->background, COLOR_PAIR(2));
	put_title(v);
	wattron(v->background, COLOR_PAIR(1));
	while (c != 27 && c != 10)
		c = getch();
	clear();
	box(v->background, ACS_VLINE, ACS_HLINE);
	wrefresh(v->background);
	return (c);
}

int				ft_visu(t_arena *arn)
{
	t_visu		v;

	initscr();
	noecho();
	start_color();
	curs_set(FALSE);
	if (init_visu(&v) == 27)
		return (free_visu(&v));
	wrefresh(v.background);
	box(v.arena, ACS_VLINE, ACS_HLINE);
	box(v.info, ACS_VLINE, ACS_HLINE);
	box(v.man, ACS_VLINE, ACS_HLINE);
	put_man(&v);
	game(&v, arn);
	return (free_visu(&v));
}
