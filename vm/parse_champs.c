/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:32:42 by arobion           #+#    #+#             */
/*   Updated: 2018/03/17 16:02:35 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_checkname(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	i -= 4;
	if (str[i++] != '.')
		return (0);
	if (str[i++] != 'c')
		return (0);
	if (str[i++] != 'o')
		return (0);
	if (str[i++] != 'r')
		return (0);
	return (1);
}

int		ft_checkfile(char *str)
{
	int		fd;

	if ((fd = open(str, O_RDONLY)) < 0)
		exit(0);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int		check_display(char **argv, int argc, int *display, int *i)
{
	char		*flag;

	if (ft_strlen(argv[*i]) == 2)
	{
		if (!(flag = ft_strdup(argv[*i])))
			exit(0);
		if (ft_strcmp(flag, "-v") == 0)
		{
			if (argc >= 3)
			{
				*i += 1;
				*display = 1;
			}
		}
		ft_strdel(&flag);
	}
	return (1);
}

int		parse_champs2(char **argv, int argc, int j, int *nb_player)
{
	while (j < argc)
	{
		if (!(check_number(argc, argv, &j)) || j >= argc)
			return (write_usage());
		if (ft_checkfile(argv[j]) == 0)
			return (print_no_file(argv[j]));
		if (ft_checkname(argv[j]) == 0)
		{
			ft_dprintf(2, "Error: File %s is too small to be a champion\n"\
					, argv[j]);
			return (0);
		}
		else
			(*nb_player)++;
		if (*nb_player > MAX_PLAYERS)
		{
			ft_dprintf(2, "Too many champions\n");
			return (0);
		}
		j++;
	}
	return (1);
}

int		parse_champs(int argc, char **argv, t_norme *opt)
{
	int		j;
	int		nb_player;

	nb_player = 0;
	if (argc <= 1)
		return (write_usage());
	if (!(check_dump(argv, argc, &(opt->dump), &(opt->i))) || opt->i >= argc)
		return (write_usage());
	if (!(check_display(argv, argc, &(opt->display), &(opt->i))\
				|| opt->i >= argc))
		return (write_usage());
	if (opt->display == 1)
		if (!(check_dump(argv, argc, &(opt->dump), &(opt->i)))\
				|| opt->i >= argc)
			return (write_usage());
	if (opt->display == 1 && (int)(opt->dump) != -1)
		return (write_usage());
	j = opt->i;
	if (!(parse_champs2(argv, argc, j, &nb_player)))
		return (0);
	return (nb_player);
}
