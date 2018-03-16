/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name_comments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:20:30 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/16 16:37:46 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_exit_error_line(t_file *f, t_champ *champ,
		char *message, int ret)
{
	ft_dprintf(2, "%+kerror%k: %+kline %k%d%k : %s\n",
			LRED, RESET, EOC, LGREEN, f->line_nb, RESET, message);
	ft_strdel(&f->line);
	free_return(f, champ, 0);
	exit(ret);
}

void		multiple_lines_handler_name(char **line, t_champ *champ, t_file *f)
{
	char	*tmp;
	int		ret;
	int		len;

	ret = 1;
	tmp = *line;
	len = ft_strchrindex(tmp, '"');
	if (len > PROG_NAME_LENGTH)
		ft_exit_error_line(f, champ, "champion name too long", 0);
	while (ret > 0 && !tmp[ft_strchrindex(tmp, '"')])
	{
		ft_strlcat(champ->name, tmp, PROG_NAME_LENGTH);
		ft_strdel(&f->line);
		ret = sget_next_line(f->fd_read, &f->line);
		f->line_nb++;
		tmp = f->line;
		len += ft_strchrindex(tmp, '"') + 1;
		if (len > PROG_NAME_LENGTH)
			ft_exit_error_line(f, champ, "champion name too long", 0);
	}
	*line = tmp;
}

void		multiple_lines_handler_comment(char **line, t_champ *champ,
		t_file *f)
{
	char	*tmp;
	int		ret;
	int		len;

	ret = 1;
	tmp = *line;
	len = ft_strchrindex(tmp, '"');
	if (len > COMMENT_LENGTH)
		ft_exit_error_line(f, champ, "comment too long", 0);
	while (ret > 0 && !tmp[ft_strchrindex(tmp, '"')])
	{
		ft_strlcat(champ->comment, tmp, COMMENT_LENGTH);
		ft_strdel(&f->line);
		ret = sget_next_line(f->fd_read, &f->line);
		f->line_nb++;
		tmp = f->line;
		len += ft_strchrindex(tmp, '"') + 1;
		if (len > COMMENT_LENGTH)
			ft_exit_error_line(f, champ, "comment too long", 0);
	}
	*line = tmp;
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
	multiple_lines_handler_name(&line, champ, f);
	n_len = ft_strchrindex(line, '"');
	if (!line[n_len] ||
			line[n_len + 1 + ft_strspn(line + n_len + 1, " ")] != '\0')
	{
		ft_exit_error_line(f, champ,
				"could not find ending '\"' at the end of the name", 0);
	}
	if (n_len > PROG_NAME_LENGTH)
		ft_exit_error_line(f, champ, "champion name too long", 0);
	ft_strlcat(champ->name, line, n_len + 1);
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
	multiple_lines_handler_comment(&line, champ, f);
	n_len = ft_strchrindex(line, '"');
	if (!line[n_len] || line[n_len + 1 +
			ft_strspn(line + n_len + 1, " ")] != '\0')
		ft_exit_error_line(f, champ,
				"could not find ending '\"' at the end of the comment", 0);
	if (n_len > COMMENT_LENGTH)
		ft_exit_error_line(f, champ, "comment too long", 0);
	ft_strlcat(champ->comment, line, n_len + 1);
	check->comment = 1;
}
