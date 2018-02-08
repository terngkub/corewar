/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:15:02 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/08 18:28:31 by fbabin           ###   ########.fr       */
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
	champ->instructions = NULL;
	champ->labels = NULL;
}

void	disp_hexlen(int fd, size_t size, int len)
{

	unsigned char	*tmp;
	int				i;

	i = len;
	if (!(tmp = (unsigned char*)ft_memalloc(i * sizeof(unsigned char))))
		return ;
	while (size)
	{
		tmp[--i] = size % 256;
		size /= 256;
	}
	write (fd, tmp, len);
	write (1, tmp, len);
	free(tmp);
}

void	write_champion(int fd, t_champ *champ)
{
	disp_hexlen(fd, COREWAR_EXEC_MAGIC, 4);
	write(fd, champ->name, PROG_NAME_LENGTH);
	disp_hexlen(fd, 23, 8);
	write(fd, champ->comment, COMMENT_LENGTH);
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
	while (sget_next_line(fd_read, &line) > 0)
	{
		line_nb++;
		if (line[0] == COMMENT_CHAR)
			continue ;
		else if (!ft_strncmp(line, NAME_CMD_STRING, 5) && !check_name(&champ, line, line_nb))
			return (-1);
		else if (!ft_strncmp(line, COMMENT_CMD_STRING, 7) && !check_comment(&champ, line, line_nb))
			return (-1);
		//else if (!check_instruction_line(line))
		//	return (-1);
		free(line);
	}
	write_champion(fd_write, &champ);
	close(fd_read);
	close(fd_write);
	return (0);
}
