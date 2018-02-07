/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name_comments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:20:30 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/07 17:22:34 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_return_error_line(int line_nb, char *message, int ret)
{
	ft_printf("ERROR, line %d : %s\n", line_nb, message);
	return (ret);
}

void		ft_exit_error_line(int line_nb, char *message, int ret)
{
	ft_printf("ERROR, line %d : %s\n", line_nb, message);
	exit (ret);
}

int			check_name(char *line, int line_nb)
{
	int		n_start;
	int		n_len;

	n_len = ft_strcspn(line, " ");
	n_start = n_len + ft_strspn(line + n_len, " ");
	if (line[n_start] != '"')
		return (ft_return_error_line(line_nb, 
			"could not find starting '\"' at the beginning of the name", 0));
	n_len = ft_strchrindex(line + n_start + 1, '"');
	if (!line[n_start + 1 + n_len] ||
			line[n_start + n_len + 2 +
			ft_strspn(line + n_start + n_len + 2, " ")] != '\0')
		return(ft_return_error_line(line_nb,
					"could not find ending '\"' at the end of the name", 0));
	if (n_len > PROG_NAME_LENGTH)
		return(ft_return_error_line(line_nb, "champion name too long", 0));
	return (1);
}

int			check_comment(char *line, int line_nb)
{
	int		n_start;
	int		n_len;

	n_len = ft_strcspn(line, " ");
	n_start = n_len + ft_strspn(line + n_len, " ");
	if (line[n_start] != '"')
		return (ft_return_error_line(line_nb, 
			"could not find starting '\"' at the beginning of the comment", 0));
	n_len = ft_strchrindex(line + n_start + 1, '"');
	if (!line[n_start + 1 + n_len] ||
			line[n_start + n_len + 2 +
			ft_strspn(line + n_start + n_len + 2, " ")] != '\0')
		return(ft_return_error_line(line_nb,
					"could not find ending '\"' at the end of the comment", 0));
	if (n_len > COMMENT_LENGTH)
		return(ft_return_error_line(line_nb, "comment too long", 0));
	return (1);
}
