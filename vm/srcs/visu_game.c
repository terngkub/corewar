/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <pnardozi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:06:28 by pnardozi          #+#    #+#             */
/*   Updated: 2018/03/03 15:41:38 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		game4(t_arena *arn, t_visu *v, int key)
{
	if (arn->nb_cycle == v->next_cycle_to_die)
		kill_and_refresh_processes(arn, &(arn->process),\
				&v->next_cycle_to_die, &v->cycle_to_die);
	run_processes(arn);
	arn->nb_cycle++;
	put_arena(*v, (const char*)arn->mem, (const char*)arn->color);
	wrefresh(v->arena);
	put_info(*v, arn, 0, key);
	refresh_color_process(arn->color);
}

static void		game3(t_arena *arn, t_visu *v, int *i, char *c)
{
	*i = -1;
	*c = 0;
	v->proc = 0;
	put_info(*v, arn, 0, 2);
	put_arena(*v, (const char*)arn->mem, (const char*)arn->color);
	wrefresh(v->arena);
}

static int		game2(char *c, t_visu *v, t_arena *arn)
{
	while (1)
	{
		*c = getch();
		put_info(*v, arn, 0, 2);
		if (*c == 32)
			return (1);
		if (*c == 100)
			return (1);
		if (*c == 27)
			return (0);
	}
	return (0);
}

static int		game1(char c, int *key)
{
	*key = 1;
	while (c != 100 && c != 32)
	{
		c = getch();
		if (c == 32)
			*key = 0;
		if (c == 27)
			return (0);
	}
	return (1);
}

void			game(t_visu *v, t_arena *arn)
{
	int			i;
	char		c;
	int			key;

	game3(arn, v, &i, &c);
	while (c != 32 && c != 27 && c != 100)
		c = getch();
	nodelay(stdscr, 1);
	while ((v->proc = nb_of_process(&(arn->process))) && c != 27)
	{
		set_color_process(arn->color, arn->process);
		if (c == 100 || key == 1)
			if (!(game1(c, &key)))
				return ;
		c = getch();
		if (c == 32)
			if (!(game2(&c, v, arn)))
				return ;
		game4(arn, v, key);
	}
	put_winner(arn, v);
	if (c != 27)
		while (getch() != 27)
			;
}
