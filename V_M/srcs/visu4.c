/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <pnardozi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 13:09:21 by pnardozi          #+#    #+#             */
/*   Updated: 2018/03/02 17:17:34 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	set_colorx(void)
{
	init_color(COLOR_LGREY, 600, 600, 600);
	init_color(COLOR_NRED, 700, 40, 50);
	init_color(COLOR_TRED, 1000, 200, 0);
	init_color(COLOR_LGREEN, 40, 600, 100);
	init_color(COLOR_LYELLOW, 700, 600, 40);
	init_color(COLOR_LBLUE, 90, 60, 770);
	init_color(COLOR_WGREEN, 350, 800, 300);
	init_pair(1, COLOR_LGREY, 0);
	init_pair(2, COLOR_TRED, 0);
	init_pair(3, COLOR_NRED, 0);
	init_pair(4, COLOR_LGREEN, 0);
	init_pair(5, COLOR_LYELLOW, 0);
	init_pair(6, COLOR_LBLUE, 0);
	init_pair(7, COLOR_WGREEN, 0);
	init_pair(10, COLOR_WHITE, COLOR_LGREY);
	init_pair(11, COLOR_WHITE, COLOR_NRED);
	init_pair(12, COLOR_WHITE, COLOR_LGREEN);
	init_pair(13, COLOR_WHITE, COLOR_LYELLOW);
	init_pair(14, COLOR_WHITE, COLOR_LBLUE);
	init_pair(15, COLOR_WHITE, 0);
}

void	put_title(t_visu *v)
{
	mvwprintw(v->background, 31, 150, \
	" _____ ___________ _____ _    _  ___  ______             ___  _____");
	mvwprintw(v->background, 32, 150, \
	"/  __ \\  _  | ___ \\  ___| |  | |/ _ \\ | ___ \\");
	mvwprintw(v->background, 32, 206, "/   |/ __  \\");
	mvwprintw(v->background, 33, 150, \
	"| /  \\/ | | | |_/ / |__ | |  | / /_\\ \\| |_/ /          / /| |`' / /'");
	mvwprintw(v->background, 34, 150, \
	"| |   | | | |    /|  __|| |/\\| |  _  ||    /          / /_| |  / /");
	mvwprintw(v->background, 35, 150, \
	"| \\__/\\ \\_/ / |\\ \\| |___\\  /\\  / | | || |\\");
	mvwprintw(v->background, 35, 193, "\\          \\___  |./ /___");
	mvwprintw(v->background, 36, 150, \
	" \\____/\\___/\\_| \\_\\____/ \\/  \\/\\_| |_/\\_|");
	mvwprintw(v->background, 36, 192, "\\_|             |_/\\_____/");
	mvwprintw(v->background, 40, 157,\
	" ___ ___ ___ ___ ___        ___ _  _ _____ ___ ___ ");
	mvwprintw(v->background, 41, 157, \
	"| _ | _ | __/ __/ __|      | __| \\| |_   _| __| _ \\");
	mvwprintw(v->background, 42, 157, \
	"|  _|   | _|\\__ \\__ \\      | _|| .` | | | | _||   /");
	mvwprintw(v->background, 43, 157, \
	"|_| |_|_|___|___|___/      |___|_|\\_| |_| |___|_|_\\");
}
