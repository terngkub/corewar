/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:15:02 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/08 20:41:29 by nkamolba         ###   ########.fr       */
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

void	ft_initchamp(t_champ *champ)
{
	ft_bzero(champ->name, PROG_NAME_LENGTH + 1);
	ft_bzero(champ->comment, COMMENT_LENGTH + 1);
	champ->inst = NULL;
	champ->labels = NULL;
}


int		main(int argc, char **argv)
{
	int			fd_read;
	int			fd_write;
	char		*cor_filename;
	char		*line;
	int			line_nb;
	t_champ		champ;

	ft_initchamp(&champ);
	line_nb = 0;
	if (argc != 2 || !check_file_name(argv[1]))
		ft_error("wrong input");
	fd_read = open(argv[1], O_RDONLY);
	cor_filename = get_cor_name(argv[1]);
	fd_write = open(cor_filename, O_WRONLY | O_CREAT, 0755);
	ft_fprintf(fd_write, "%c%c%c%c", 0x00, 0xea, 0x83, 0xf3);
	while (sget_next_line(fd_read, &line) > 0)
	{
		line_nb++;
		/*
		if (!ft_strncmp(line, NAME_CMD_STRING, 5))
			ft_printf("%d\n", check_name(&champ, line, line_nb));
		else if (!ft_strncmp(line, COMMENT_CMD_STRING, 7))
			ft_printf("%d\n", check_comment(&champ, line, line_nb));
		else
			ft_printf("%d\n", check_instruction_line(&champ, line));
			*/
		ft_printf("%s\n", line);
		if (line[0] == COMMENT_CHAR)
			continue ;
		else if (!ft_strncmp(line, NAME_CMD_STRING, 5) && !check_name(&champ, line, line_nb))
			return (-1);
		else if (!ft_strncmp(line, COMMENT_CMD_STRING, 7) && !check_comment(&champ, line, line_nb))
			return (-1);
		else if (!check_instruction_line(&champ, line))
			return (-1);
		free(line);
	}
	print_inst_list(champ.inst);
	print_labels_list(champ.labels);
	write(fd_write, champ.name, PROG_NAME_LENGTH);
	write(fd_write, champ.comment, COMMENT_LENGTH);
	close(fd_read);
	close(fd_write);
	return (0);
}
