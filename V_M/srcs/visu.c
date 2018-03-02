/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <pnardozi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 13:43:32 by pnardozi          #+#    #+#             */
/*   Updated: 2018/03/02 16:30:22 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	put_info(t_visu v, t_arena *arn, int win, int run)
{
	int		i;
	int		u;

	u = 16;
	i = -1;
	if (win)
	{
		wattron(v.info, A_UNDERLINE | COLOR_PAIR(7));
		mvwprintw(v.info, 2, 2, "The winner is %s !", arn->players[win - 1].name);
		wattroff(v.info, A_UNDERLINE);
		wattron(v.info, COLOR_PAIR(1));
	}
	if (run == 1)
	{
		wattron(v.info, COLOR_PAIR(14));
		mvwprintw(v.info, 4, 2, "%7s", "1 BY 1");
		wattron(v.info, COLOR_PAIR(1));
	}
	else if (run == 2)
	{
		wattron(v.info, COLOR_PAIR(14));
		mvwprintw(v.info, 4, 2, "%7s", "PAUSE");
		wattron(v.info, COLOR_PAIR(1));
	}
	else if (run == 3)
	{
		wattron(v.info, COLOR_PAIR(14));
		mvwprintw(v.info, 4, 2, "%7s", "DONE");
		wattron(v.info, COLOR_PAIR(1));
	}
	else
	{
		wattron(v.info, COLOR_PAIR(14));
		mvwprintw(v.info, 4, 2, "RUNNING");
		wattron(v.info, COLOR_PAIR(1));
	}
	mvwprintw(v.info, 6, 2, "Cycles : %5d", arn->nb_cycle);
	mvwprintw(v.info, 8, 2, "Processes : %5d", v.proc);
	if (run == 3)
		v.cycle_to_die = 0;
	mvwprintw(v.info, 10, 2, "CYCLE TO DIE : %5d", v.cycle_to_die);
	mvwprintw(v.info, 12, 2, "CYCLE_DELTA : %5d", CYCLE_DELTA);
	mvwprintw(v.info, 14, 2, "NBR_LIVE : %5d", NBR_LIVE);
	mvwprintw(v.info, 16, 2, "MAX_CHECKS : %5d", MAX_CHECKS);
	while(++i < arn->nb_players)
	{
		wattron(v.info, COLOR_PAIR(arn->players[i].number + 2));
		mvwprintw(v.info, u, 2, "Player %3d : %3s", arn->players[i].number, arn->players[i].name);
		wattron(v.info, COLOR_PAIR(1));
		mvwprintw(v.info, u + 1, 3, "Last live : %5d", arn->players[i].last_live);
		mvwprintw(v.info, u + 2, 3, "Lives in current period : %5d", arn->players[i].nb_live);
		u += 5;
	}
	wrefresh(v.info);
}

void	game(t_visu *v, t_arena *arn)
{
	int			i;
	char		c;
	int			key;

	i = -1;
	c = 0;
	curs_set(FALSE);
	v->proc = 0;
	put_info(*v, arn, 0, 2);
	put_arena(*v, (const char*)arn->mem, (const char*)arn->color);
	while (c != 32 && c != 27 && c != 100)
		c = getch();
	nodelay(stdscr, 1);
	while ((v->proc = nb_of_process(&(arn->process))) && c != 27)
	{
		set_color_process(arn->color, arn->process);
		if (c == 100 || key == 1)
		{
			key = 1;
			while (c != 100 && c != 32)
			{
				c = getch();

				if (c == 32)
					key = 0;
				if (c == 27)
					return ;
			}
		}
		c = getch();
		if (c == 32)
			while (1)
			{ 
				c = getch();
				put_info(*v, arn, 0, 2);
				if (c == 32)
					break ;
				if (c == 100)
					break ;
				if (c == 27)
					return ;
			}	
		if (arn->nb_cycle == v->next_cycle_to_die)
			kill_and_refresh_processes(arn, &(arn->process),\
					&v->next_cycle_to_die, &v->cycle_to_die);
		run_processes(arn);
		arn->nb_cycle++;
		put_arena(*v, (const char*)arn->mem, (const char*)arn->color);
		put_info(*v, arn, 0, key);
		refresh_color_process(arn->color);
	}
	if (c != 27)
	{
		put_winner(arn, v);
		while(getch() != 27);
	}
}

int		init_visu(t_visu *v)
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

int		ft_visu(t_arena *arn)
{
	t_visu		v;

	initscr();
	noecho();
	start_color();
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
