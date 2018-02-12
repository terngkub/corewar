/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 20:36:26 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/12 20:39:56 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	init_champ(t_champ *champ)
{
	ft_bzero(champ->name, PROG_NAME_LENGTH + 1);
	ft_bzero(champ->comment, COMMENT_LENGTH + 1);
	champ->accu_len = 0;
	champ->inst = NULL;
	champ->labels = NULL;
}

static void	init_check(t_check *check)
{
	check->name = 0;
	check->comment = 0;
}

static void	init_file(t_file *f)
{
	f->line_nb = 0;
	f->line = NULL;
	f->fd_read = 0;
	f->cor_filename = NULL;
	f->fd_write = 0;
}

void		init_asm(t_champ *champ, t_check *check, t_file *f)
{
	init_champ(champ);
	init_check(check);
	init_file(f);
}
