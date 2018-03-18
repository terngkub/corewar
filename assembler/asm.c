/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:15:02 by nkamolba          #+#    #+#             */
/*   Updated: 2018/03/17 16:08:32 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_cor_name(char *filename)
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

static int	check_file_name(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (len > 2 && str[len - 2] == '.' && str[len - 1] == 's' && str[len] == 0)
		return (1);
	return (0);
}

int			main_2(t_file *f, t_champ *champ, t_check *check)
{
	while (sget_next_line(f->fd_read, &f->line) > 0)
	{
		f->line_nb++;
		if (f->line[0] == COMMENT_CHAR || f->line[0] == ';')
			;
		else if (!ft_strncmp(f->line + ft_strspn(f->line, " \t"),
					NAME_CMD_STRING, 5))
		{
			check_name(champ, f, check);
		}
		else if (!ft_strncmp(f->line + ft_strspn(f->line, " \t"),
					COMMENT_CMD_STRING, 7))
		{
			check_comment(champ, f, check);
		}
		else if (!check_instruction_line(champ, f->line, f->line_nb))
			return (free_return(f, champ, -1));
		ft_strdel(&f->line);
	}
	ft_strdel(&f->line);
	return (0);
}

int			main(int argc, char **argv)
{
	t_champ			champ;
	t_check			check;
	t_file			f;

	init_asm(&champ, &check, &f);
	if (argc != 2 || !check_file_name(argv[1]))
		ft_error("wrong input");
	if ((f.fd_read = open(argv[1], O_RDONLY)) == -1)
		ft_error("wrong input");
	f.cor_filename = get_cor_name(argv[1]);
	if (main_2(&f, &champ, &check) == -1)
		return (-1);
	if (!(check_integrity(&champ, &check)))
		return (free_return(&f, &champ, -1));
	if ((f.fd_write = open(f.cor_filename, O_WRONLY | O_CREAT, 0755)) == -1)
		return (free_return(&f, &champ, -1));
	write_champion(f.fd_write, &champ);
	if ((close(f.fd_read)) == -1)
		return (free_return(&f, &champ, 0));
	if ((close(f.fd_write)) == -1)
		return (free_return(&f, &champ, 0));
	ft_printf("Writing output program to %s\n", f.cor_filename);
	return (free_return(&f, &champ, 0));
}
