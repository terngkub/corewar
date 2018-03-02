/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <pnardozi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 13:09:21 by pnardozi          #+#    #+#             */
/*   Updated: 2018/03/02 13:11:59 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	color(void)
{
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
}

void	put_title(t_visu *v)
{
	mvwprintw(v->background, 31, 150, " _____ ___________ _____ _    _  ___  ______             ___  _____");
	mvwprintw(v->background, 32, 150, "/  __ \\  _  | ___ \\  ___| |  | |/ _ \\ | ___ \\           /   |/ __  \\");
	mvwprintw(v->background, 33, 150, "| /  \\/ | | | |_/ / |__ | |  | / /_\\ \\| |_/ /          / /| |`' / /'");
	mvwprintw(v->background, 34, 150, "| |   | | | |    /|  __|| |/\\| |  _  ||    /          / /_| |  / /");
	mvwprintw(v->background, 35, 150, "| \\__/\\ \\_/ / |\\ \\| |___\\  /\\  / | | || |\\ \\          \\___  |./ /___");
	mvwprintw(v->background, 36, 150, " \\____/\\___/\\_| \\_\\____/ \\/  \\/\\_| |_/\\_| \\_|             |_/\\_____/");
	mvwprintw(v->background, 40, 157," ___ ___ ___ ___ ___        ___ _  _ _____ ___ ___ ");
	mvwprintw(v->background, 41, 157, "| _ | _ | __/ __/ __|      | __| \\| |_   _| __| _ \\");
	mvwprintw(v->background, 42, 157, "|  _|   | _|\\__ \\__ \\      | _|| .` | | | | _||   /");
	mvwprintw(v->background, 43, 157, "|_| |_|_|___|___|___/      |___|_|\\_| |_| |___|_|_\\");
}
