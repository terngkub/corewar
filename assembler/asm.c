/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:15:02 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/07 18:17:43 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_cor_name(char *filename)
{
	int		len;
	char	*cor_filename;

	len = ft_strlen(filename);
	if (!(cor_filename = ft_strnew(len + 2)))
		ft_error("malloc failed");
	ft_strncpy(cor_filename, filename, len - 1);
	ft_strcat(cor_filename, "cor");
	return (cor_filename);
}

int		check_file_name(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (len > 2 && str[len - 2] == '.' && str[len - 1] == 's' && str[len] == 0)
		return (1);
	return (0);
}

int		main(int argc, char **argv)
{
	int		fd_read;
	int		fd_write;
	char	*cor_filename;
	char	*line;
	int		line_nb;

	line_nb = 0;
	if (argc != 2 || !check_file_name(argv[1]))
		ft_error("wrong input");
	fd_read = open(argv[1], O_RDONLY);
	cor_filename = get_cor_name(argv[1]);
	fd_write = open(cor_filename, O_WRONLY | O_CREAT, 0755);
	while (sget_next_line(fd_read, &line) > 0)
	{
		line_nb++;
		if (!ft_strncmp(line, NAME_CMD_STRING, 5))
			ft_printf("%d\n", check_name(line, line_nb));
		if (!ft_strncmp(line, COMMENT_CMD_STRING, 7))
			ft_printf("%d\n", check_comment(line, line_nb));
		//ft_fprintf(fd_write, "%s\n", line);
		free(line);
	}
	close(fd_read);
	close(fd_write);
	return (0);
}
