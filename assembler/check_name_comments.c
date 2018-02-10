/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name_comments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:20:30 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/10 18:16:16 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_return_error_line(int line_nb, char *message, int ret)
{
	ft_printf("\033[01;31mERROR{eoc}: line \033[01;32m%d{eoc} : %s\n", line_nb, message);
	return (ret);
}

void		ft_exit_error_line(int line_nb, char *message, int ret)
{
	ft_printf("\033[01;31mERROR{eoc}: line \033[01;32m%d{eoc} : %s\n", line_nb, message);
	exit (ret);
}

int			check_name(t_champ *champ, t_file *f, t_check *check)
{
	int		n_start;
	int		n_len;
	int		ret;

	ret = 1;
	n_len = ft_strcspn(f->line, " \t");
	n_start = n_len + ft_strspn(f->line + n_len, " \t");
	if (check->name == 1)
		return (ft_return_error_line(f->line_nb,
			"champion already has a name", 0));
	if (f->line[n_start] != '"')
		return (ft_return_error_line(f->line_nb, 
			"could not find starting '\"' at the beginning of the name", 0));
	f->line += n_start + 1;
	while (ret > 0 && !ft_charinset(':', f->line) && !f->line[ft_strchrindex(f->line, '"')])
	{
		ft_strcat(champ->name, f->line);
		ret = sget_next_line(f->fd_read, &f->line);
	}
	n_len = ft_strchrindex(f->line, '"');
	if (!f->line[n_len] || f->line[n_len + 1 + 
			ft_strspn(f->line + n_len + 1, " ")] != '\0')
		return(ft_return_error_line(f->line_nb,
					"could not find ending '\"' at the end of the name", 0));
	if (n_len > PROG_NAME_LENGTH)
		return(ft_return_error_line(f->line_nb, "champion name too long", 0));
	ft_strncat(champ->name, f->line, n_len);
	check->name = 1;
	return (1);
}

int			check_comment(t_champ *champ, t_file *f, t_check *check)
{
	int		n_start;
	int		n_len;

	n_len = ft_strcspn(f->line, " \t");
	n_start = n_len + ft_strspn(f->line + n_len, " \t");
	if (check->comment == 1)
		return (ft_return_error_line(f->line_nb,
			"champion already has a comment", 0));
	if (f->line[n_start] != '"')
		return (ft_return_error_line(f->line_nb, 
			"could not find starting '\"' at the beginning of the comment", 0));
	f->line += n_start + 1;
	while (!ft_strbspn(f->line, ":") && !f->line[ft_strchrindex(f->line, '"')])
	{
		ft_strcat(champ->name, f->line);
		sget_next_line(f->fd_read, &f->line);
	}
	n_len = ft_strchrindex(f->line, '"');
	if (!f->line[n_len] ||
			f->line[n_len + 1 +
			ft_strspn(f->line + n_len + 1, " ")] != '\0')
		return(ft_return_error_line(f->line_nb,
					"could not find ending '\"' at the end of the comment", 0));
	if (n_len > COMMENT_LENGTH)
		return(ft_return_error_line(f->line_nb, "comment too long", 0));
	ft_strncat(champ->name, f->line, n_len);
	check->comment = 1;
	return (1);
}
