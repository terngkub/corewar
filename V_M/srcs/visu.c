/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:30:35 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/01 15:45:47 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdio.h>

void	f_p(char *byte, char mem)
{
	unsigned char	tmp;
	char			base[17];

	ft_memcpy((char*)base, "0123456789abcdef\0", 17);
	tmp = (unsigned char) mem;
	byte[0] = base[tmp / 16];
	byte[1] = base[tmp % 16];
}

void    set_color(t_visu v, char c)
{
	if (c == 1)
		wattron(v.arena, COLOR_PAIR(c));
	if (c == 2)
		wattron(v.arena, COLOR_PAIR(c));
	if (c == 3)
		wattron(v.arena, COLOR_PAIR(c));
	if (c == -1)
		wattron(v.arena, COLOR_PAIR(ft_abs(c) + 3));
	if (c == -2)
		wattron(v.arena, COLOR_PAIR(ft_abs(c) + 3));
	if (c == -3)
		wattron(v.arena, COLOR_PAIR(ft_abs(c) + 3));
}

void    put_arena(t_visu v, const char *mem, const char *color)
{
	int             i;
	int             x;
	int             y;
	char    byte[5];

	x = 0;
	y = 0;
	i = -1;

	ft_bzero(&byte, 5);
	while (++i < 4096)
	{

		f_p((char*)byte, mem[i]);
		if (((i % 64) == 0) && i != 0)
		{
			y += 1;
			x = 0;
		}
		else
		{
			byte[2] = ' ';
			byte[3] = ' ';
		}
		set_color(v, color[i]);
		if (color[i] < 0)
		{
			byte[2] = '\0';
			mvwprintw(v.arena, y + 1, x + 3, (char*)&byte);
			wattron(v.arena, COLOR_PAIR(14));
			mvwprintw(v.arena, y + 1, x + 5, "  ");
		}
		else
			mvwprintw(v.arena, y + 1, x + 3, (char*)&byte);
		x += 4;
	}
	wrefresh(v.arena);
}

void	init_visu(t_visu *v)
{
	WINDOW		*tmp;

	initscr();
	noecho();
	start_color();
	init_color(COLOR_LGREY, 600, 600, 600);
	init_color(COLOR_NRED, 1000, 300, 250);
	init_color(COLOR_NGREEN, 300, 1000, 250);
	init_pair(1, COLOR_LGREY, 0);
	init_pair(4, COLOR_WHITE, COLOR_LGREY);
	init_pair(5, COLOR_WHITE, COLOR_NRED);
	init_pair(6, COLOR_WHITE, COLOR_LBLUE);
	init_pair(2, COLOR_NRED, 0);
	init_pair(3, COLOR_LBLUE, 0);
	init_pair(14, COLOR_WHITE, 0);
	v->cycle_to_die = CYCLE_TO_DIE;
	v->next_cycle_to_die = CYCLE_TO_DIE;
	v->arena = subwin(stdscr, 66, 260, 1, 5);
	v->info = subwin(stdscr, 66, 90, 1, COLS - 95);
	v->background = subwin(stdscr, LINES, COLS, 0, 0);
	tmp = subwin(stdscr, 50, 90, 30, 150);
	wattron(v->background, COLOR_PAIR(1));
	box(v->background, ACS_VLINE, ACS_HLINE);
	wattron(tmp, COLOR_PAIR(2));
	wattron(v->arena, COLOR_PAIR(1));
	wattron(v->info, COLOR_PAIR(1));
	mvwprintw(tmp, 0, 0, " _____ ___________ _____ _    _  ___  ______             ___  _____\n");
	mvwprintw(tmp, 1, 0, "/  __ \\  _  | ___ \\  ___| |  | |/ _ \\ | ___ \\           /   |/ __  \\\n");
	mvwprintw(tmp, 2, 0, "| /  \\/ | | | |_/ / |__ | |  | / /_\\ \\| |_/ /          / /| |`' / /'\n");
	mvwprintw(tmp, 3, 0, "| |   | | | |    /|  __|| |/\\| |  _  ||    /          / /_| |  / /\n");
	mvwprintw(tmp, 4, 0, "| \\__/\\ \\_/ / |\\ \\| |___\\  /\\  / | | || |\\ \\          \\___  |./ /___\n");
	mvwprintw(tmp, 5, 0, " \\____/\\___/\\_| \\_\\____/ \\/  \\/\\_| |_/\\_| \\_|             |_/\\_____/\n");
	mvwprintw(tmp, 10, 7," ___ ___ ___ ___ ___        ___ _  _ _____ ___ ___ \n");
	mvwprintw(tmp, 11, 7, "| _ | _ | __/ __/ __|      | __| \\| |_   _| __| _ \\\n");
	mvwprintw(tmp, 12, 7, "|  _|   | _|\\__ \\__ \\      | _|| .` | | | | _||   /\n");
	mvwprintw(tmp, 13, 7, "|_| |_|_|___|___|___/      |___|_|\\_| |_| |___|_|_\\\n");
	while (getch() != 10);
	clear();
	box(v->background, ACS_VLINE, ACS_HLINE);
	wrefresh(v->background);
}

void	put_info(t_visu v, t_arena *arn, int win, int run)
{
	int		i;
	int		u;

	u = 16;
	i = -1;
	if (win)
	{
		wattron(v.info, A_UNDERLINE | COLOR_PAIR(3));
		mvwprintw(v.info, 2, 2, "The winner is %s !", arn->players[win - 1].name);
		wattroff(v.info, A_UNDERLINE);
		wattron(v.info, COLOR_PAIR(1));
	}
	if (run == 1)
	{
		wattron(v.info, COLOR_PAIR(3));
		mvwprintw(v.info, 4, 2, "%7s", "PAUSE");
		wattron(v.info, COLOR_PAIR(1));
	}
	else if (run == 2)
	{
		wattron(v.info, COLOR_PAIR(3) | A_BOLD);
		mvwprintw(v.info, 4, 2, "%7s", "DONE");
		wattron(v.info, COLOR_PAIR(1));
	}
	else
	{
		wattron(v.info, COLOR_PAIR(6));
		mvwprintw(v.info, 4, 2, "RUNNING");
		wattron(v.info, COLOR_PAIR(1));
	}
	mvwprintw(v.info, 6, 2, "Cycles : %5d", arn->nb_cycle);
	mvwprintw(v.info, 8, 2, "Processes : %5d", v.proc);
	mvwprintw(v.info, 10, 2, "CYCLE TO DIE : %5d", v.cycle_to_die);
	mvwprintw(v.info, 12, 2, "CYCLE_DELTA : %5d", CYCLE_DELTA);
	mvwprintw(v.info, 14, 2, "NBR_LIVE : %5d", NBR_LIVE);
	mvwprintw(v.info, 16, 2, "MAX_CHECKS : %5d", MAX_CHECKS);
	mvwprintw(v.info, 18, 2, "Cycles / sec : ");
	while(++i < arn->nb_players)
	{
		mvwprintw(v.info, u, 2, "Player %3d : %3s", arn->players[i].number, arn->players[i].name);
		mvwprintw(v.info, u + 1, 3, "Last live : %5d", arn->players[i].last_live);
		mvwprintw(v.info, u + 2, 3, "Lives in current period : %5d", arn->players[i].nb_live);
		u += 5;
	}
	wrefresh(v.info);
}

void	set_color_process(char *color, t_process *begin_list)
{
	t_process	*lst;

	lst = begin_list;
	while (lst)
	{
		color[lst->pc] *= -1;
		lst = lst->next;
	}
}

void	refresh_color_process(char *str)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (str[i] < 0)
			str[i] *= -1;
		i++;
	}
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
	put_info(*v, arn, winner, 2);

}

void	game(t_visu *v, t_arena *arn)
{
	int			i;

	i = -1;
	curs_set(FALSE);
	v->proc = 0;
	put_info(*v, arn, 0, 1);
	put_arena(*v, (const char*)arn->mem, (const char*)arn->color);
	while (getch() != 32);
	nodelay(stdscr, 1);
	while ((v->proc = nb_of_process(&(arn->process))))
	{
		set_color_process(arn->color, arn->process);
		if (getch() == 32)
			while (getch() != 32)
				put_info(*v, arn, 0, 1);
		if (arn->nb_cycle == v->next_cycle_to_die)
			kill_and_refresh_processes(arn, &(arn->process),\
					&v->next_cycle_to_die, &v->cycle_to_die);
		run_processes(arn);
		arn->nb_cycle++;
		put_arena(*v, (const char*)arn->mem, (const char*)arn->color);
		put_info(*v, arn, 0, 0);
		refresh_color_process(arn->color);
	}
	put_winner(arn, v);
	while(getch() != 10);
}

int		ft_visu(t_arena *arn)
{
	t_visu		v;

	init_visu(&v);
	wrefresh(v.background);
	box(v.arena, ACS_VLINE, ACS_HLINE);
	box(v.info, ACS_VLINE, ACS_HLINE);
	game(&v, arn);
	endwin();
	free(v.arena);
	free(v.info);
	free(v.background);
	return (0);
}
