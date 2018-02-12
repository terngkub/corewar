/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name_comments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:20:30 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/12 14:37:22 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_return_error_line(t_file *f, char *message, int ret)
{
	ft_putendl(f->line);
	ft_printf("\033[01;31merror{eoc}: line \033[01;32m%d{eoc} : %s\n",
		f->line_nb, message);
	free(f->line);
	return (ret);
}

void		ft_exit_error_line(t_file *f, t_champ *champ,
				char *message, int ret)
{
	ft_putendl(f->line);
	ft_printf("\033[01;31merror{eoc}: line \033[01;32m%d{eoc} : %s\n",
		f->line_nb, message);
	free(f->line);
	free_return(f, champ, 0);
	exit(ret);
}

void		multiple_lines_handler_name(char *line, t_champ *champ, t_file *f)
{
	int		ret;

	ret = 1;
	while (ret > 0 && !ft_charinset(':', line) &&
		!line[ft_strchrindex(line, '"')])
	{
		ft_strcat(champ->name, line);
		free(f->line);
		ret = sget_next_line(f->fd_read, &f->line);
		f->line_nb++;
		line = f->line;
	}
}

void		multiple_lines_handler_comment(char *line, t_champ *champ, t_file *f)
{
	int		ret;

	ret = 1;
	while (ret > 0 && !ft_charinset(':', line) &&
		!line[ft_strchrindex(line, '"')])
	{
		ft_strcat(champ->comment, line);
		free(f->line);
		ret = sget_next_line(f->fd_read, &f->line);
		f->line_nb++;
		line = f->line;
	}
}

void		check_name(t_champ *champ, t_file *f, t_check *check)
{
	int		n_start;
	int		n_len;
	char	*line;

	line = f->line + ft_strspn(f->line, " \t");
	n_len = ft_strcspn(line, " \t");
	n_start = n_len + ft_strspn(line + n_len, " \t");
	if (check->name == 1)
		ft_exit_error_line(f, champ, "champion already has a name", 0);
	if (line[n_start] != '"')
		ft_exit_error_line(f, champ,
			"could not find starting '\"' at the beginning of the name", 0);
	line += n_start + 1;
	multiple_lines_handler_name(line, champ, f);
	n_len = ft_strchrindex(line, '"');
	if (!line[n_len] || line[n_len + 1 +
		ft_strspn(line + n_len + 1, " ")] != '\0')
	{
		ft_exit_error_line(f, champ,
			"could not find ending '\"' at the end of the name", 0);
	}
	if (n_len > PROG_NAME_LENGTH)
		ft_exit_error_line(f, champ, "champion name too long", 0);
	ft_strncat(champ->name, line, n_len);
	check->name = 1;
}

void		check_comment(t_champ *champ, t_file *f, t_check *check)
{
	int		n_start;
	int		n_len;
	char	*line;

	line = f->line + ft_strspn(f->line, " \t");
	n_len = ft_strcspn(line, " \t");
	n_start = n_len + ft_strspn(line + n_len, " \t");
	if (check->comment == 1)
		ft_exit_error_line(f, champ, "champion already has a comment", 0);
	if (line[n_start] != '"')
		ft_exit_error_line(f, champ,
			"could not find starting '\"' at the beginning of the comment", 0);
	line += n_start + 1;
	multiple_lines_handler_comment(line, champ, f);
	n_len = ft_strchrindex(line, '"');
	if (!line[n_len] ||
			line[n_len + 1 +
			ft_strspn(line + n_len + 1, " ")] != '\0')
		ft_exit_error_line(f, champ,
					"could not find ending '\"' at the end of the comment", 0);
	if (n_len > COMMENT_LENGTH)
		ft_exit_error_line(f, champ, "comment too long", 0);
	ft_strncat(champ->comment, line, n_len);
	check->comment = 1;
}
