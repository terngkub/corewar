/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:30:35 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/22 19:48:53 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdio.h>

void	f_p(char *byte, char mem)
{
	unsigned char	tmp;
	char			infoe[17];

	ft_memcpy((char*)infoe, "0123456789abcdef\0", 17);
	tmp = (unsigned char) mem;
	byte[0] = infoe[tmp / 16];
	byte[1] = infoe[tmp % 16];
}

/*void	mem_to_string(const char *mem, char *str)
{
	int		i;
	int		pos;
	char	byte[3];

	i = -1;
	pos = 0;
	ft_bzero(&byte, 3);
	(void)mem;
	while (++i < 4096)
	{
		f_p((char*)byte, mem[i]);
		if (((i % 64) == 0) && i != 0)
		{
			if (i != 0)
			{
				ft_memcpy(str + pos++, "\n", 1);
				ft_memcpy(str + pos, (char*)byte, 3);
				pos += 3;
				continue ;
			}
		}
		else
		{
			byte[2] = ' ';
			ft_memcpy(str + pos, (char*)byte, 3);
		}
		pos += 3;
	}
}*/

void	put_arena(t_visu v, const char *mem, const char *color)
{
	int		i;
	int		x;
	int		y;
	char	byte[5];

	x = 0;
	y = 0;
	i = -1;
	//start_color();
	//init_color(COLOR_RED, 1000, 300, 140);
	//init_pair(1, COLOR_RED, COLOR_BLACK);
	(void)color;
	ft_bzero(&byte, 5);
	while (++i < 4096)
	{
		attron(COLOR_PAIR(color[i]));
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
		mvwprintw(v.arena, y + 1, x + 3, (char*)&byte);
		x += 4;
	}
	wrefresh(v.arena);
}

void	init_visu(t_visu *v)
{
	initscr();
	noecho();
	WINDOW		*tmp;
	WINDOW		*ttmp;
	v->cycle_to_die = CYCLE_TO_DIE;
	v->next_cycle_to_die = CYCLE_TO_DIE;
	v->arena = subwin(stdscr, 66, 260, 1, 5);    
	v->info = subwin(stdscr, 66, 90, 1, COLS - 95); 
	v->background = subwin(stdscr, LINES, COLS, 0, 0);
	tmp = subwin(stdscr, 50, 90, 30, 150);
	ttmp = subwin(stdscr, 40, 60, 40, 157);
	box(v->background, ACS_VLINE, ACS_HLINE);
	start_color();
	init_color(COLOR_RED, 1000, 300, 140);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	
	//box(tmp, ACS_VLINE, ACS_HLINE);
	mvwprintw(tmp, 0, 0, " _____ ___________ _____ _    _  ___  ______             ___  _____\n/  __ \\  _  | ___ \\  ___| |  | |/ _ \\ | ___ \\           /   |/ __  \\\n| /  \\/ | | | |_/ / |__ | |  | / /_\\ \\| |_/ /          / /| |`' / /'\n| |   | | | |    /|  __|| |/\\| |  _  ||    /          / /_| |  / /\n| \\__/\\ \\_/ / |\\ \\| |___\\  /\\  / | | || |\\ \\          \\___  |./ /___\n\\____/\\___/\\_| \\_\\____/ \\/  \\/\\_| |_/\\_| \\_|             |_/\\_____/\n");
	//mvwprintw(tmp, 0, 0, "/  __ \\  _  | ___ \\  ___| |  | |/ _ \\ | ___ \\   /   |/ __  \\\n| /  \\/ | | | |_/ / |__ | |  | / /_\\ \\| |_/ /  / /| |`' / /'\n| |   | | | |    /|  __|| |/\\| |  _  ||    /  / /_| |  / /\n| \\__/\\ \\_/ / |\\ \\| |___\\  /\\  / | | || |\\ \\  \\___  |./ /___\n\\____/\\___/\\_| \\_\\____/ \\/  \\/\\_| |_/\\_| \\_|     |_/\\_____/\n");
	//mvwprintw(tmp, 0, 0, "/  __ \\  _  | ___ \\  ___| |  | |/ _ \\ | ___ \\   /   |/ __  \\\n| /  \\/ | | | |_/ / |__ | |  | / /_\\ \\| |_/ /  / /| |`' / /'\n| |   | | | |    /|  __|| |/\\| |  _  ||    /  / /_| |  / /\n| \\__/\\ \\_/ / |\\ \\| |___\\  /\\  / | | || |\\ \\  \\___  |./ /___\n\\____/\\___/\\_| \\_\\____/ \\/  \\/\\_| |_/\\_| \\_|     |_/\\_____/\n");
	
	mvwprintw(ttmp, 0, 0," ___ ___ ___ ___ ___        ___ _  _ _____ ___ ___ \n| _ | _ | __/ __/ __|      | __| \\| |_   _| __| _ \\\n|  _|   | _|\\__ \\__ \\      | _|| .` | | | | _||   /\n|_| |_|_|___|___|___/      |___|_|\\_| |_| |___|_|_\\\n");
	//mvwprintw(tmp, 7, 0," ___ ___ ___ ___ ___              ___ _  _ _____ ___ ___ \n| _ | _ | __/ __/ __|            | __| \\| |_   _| __| _ \\\n|  _|   | _|\\__ \\__ \\            | _|| .` | | | | _||   /\\\n|_| |_|_|___|___|___/            |___|_|\\_| |_| |___|_|_\\\n");

	//mvwprintw(v->background, 30, 100, "PRESS ENTER");

	while (getch() != 10)
		;
	clear();
	box(v->background, ACS_VLINE, ACS_HLINE);
	//v->background = subwin(stdscr, LINES, COLS, 0, 0);
	wrefresh(v->background);
}

void	put_info(t_visu v, t_arena *arn)
{
	int		i;
	int		u;

	(void)arn;
	mvwprintw(v.info, 2, 2, "Cycles : %d", arn->nb_cycle);
	mvwprintw(v.info, 4, 2, "Processes : %d", v.proc);
	mvwprintw(v.info, 6, 2, "CYCLE TO DIE : %4d", v.cycle_to_die);
	mvwprintw(v.info, 8, 2, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(v.info, 10, 2, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(v.info, 12, 2, "MAX_CHECKS : %d", MAX_CHECKS);
	mvwprintw(v.info, 14, 2, "Cycles / sec : ");
	u = 16;
	i = -1;
	while(++i < arn->nb_players)
	{
		mvwprintw(v.info, u, 2, "Player %d : %s", arn->players[i].number, arn->players[i].name);
		mvwprintw(v.info, u + 1, 3, "Last live : %d", arn->players[i].last_live);
		mvwprintw(v.info, u + 2, 3, "Lives in current period : %d", arn->players[i].nb_live);
		u += 5;
		//t = t->next;
	}
	//mvwprintw(v.info, 14, 2, "Cycles / sec : ");
	//mvwprintw(v.info, 2, 2, "Cycles : %d", arn->nb_cycle);
	wrefresh(v.info);
}

void	game(t_visu *v, t_arena *arn)
{
	//	a sup
	char		color[4096];
	int			i;
	i = -1;
	while (++i < 4096)
		color[i] = 2;
	start_color();
	init_color(COLOR_RED, 1000, 300, 140);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	curs_set(FALSE);
	//
	//nodelay(stdscr,1);
	v->proc = 0;
	put_info(*v, arn);
	put_arena(*v, (const char*)arn->mem, (const char*)&color);
	getch();	
	while ((v->proc = nb_of_process(&(arn->process))))
	{
		//if (getch() != 32)
		//	nodelay(v->arena, 1);
		if (arn->nb_cycle == v->next_cycle_to_die)
			kill_and_refresh_processes(arn, &(arn->process),\
					&v->next_cycle_to_die, &v->cycle_to_die);
		run_processes(arn);
		arn->nb_cycle++;
		put_arena(*v, (const char*)arn->mem, (const char*)&color);
		put_info(*v, arn);
	}
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
