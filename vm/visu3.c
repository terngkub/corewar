/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <pnardozi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 12:08:48 by pnardozi          #+#    #+#             */
/*   Updated: 2018/03/02 16:57:29 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			set_color_process(char *color, t_process *begin_list)
{
	t_process	*lst;

	lst = begin_list;
	while (lst)
	{
		color[lst->pc] *= -1;
		lst = lst->next;
	}
}

void			refresh_color_process(char *str)
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

static void		put_arena2(int *i, int *x, int *y, char *byte)
{
	if (((*i % 64) == 0) && *i != 0)
	{
		*y += 1;
		*x = 0;
	}
	else
	{
		byte[2] = ' ';
		byte[3] = ' ';
	}
}

void			put_arena(t_visu v, const char *mem, const char *color)
{
	int		i;
	int		x;
	int		y;
	char	byte[5];

	x = 0;
	y = 0;
	i = -1;
	ft_bzero(&byte, 5);
	while (++i < 4096)
	{
		f_p((char*)byte, mem[i]);
		put_arena2(&i, &x, &y, byte);
		set_color(v, color[i]);
		if (color[i] < 0)
		{
			byte[2] = '\0';
			mvwprintw(v.arena, y + 1, x + 3, (char*)&byte);
			wattron(v.arena, COLOR_PAIR(1));
			mvwprintw(v.arena, y + 1, x + 5, "  ");
		}
		else
			mvwprintw(v.arena, y + 1, x + 3, (char*)&byte);
		x += 4;
	}
}
