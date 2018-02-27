/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:32:42 by arobion           #+#    #+#             */
/*   Updated: 2018/02/27 19:20:21 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		write_usage(void)
{
	ft_printf("Usage: ./corewar [-dump N] [-n N] <champion1.cor> <...>\n");
	return (0);
}

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

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int		print_no_file(char *str)
{
	ft_printf("Can't read source file %s\n", str);
	return (0);
}

void	check_dump2(char **argv, char **flag, int *i, int nb, unsigned int *dump, size_t len)
{
	*flag = ft_strndup(argv[*i], 0, 4);
	if (ft_strcmp(*flag, "-dump") == 0)
	{
		free(*flag);
		*flag = ft_strndup(argv[*i], 5, len);
		nb = ft_long_atoi(*flag);
		*dump = nb % 4294967296;
		*i += 1;
		free(*flag);
	}
	else
		free(*flag);
}

void	check_dump3(char **argv, char **flag, int *i, int nb, unsigned int *dump, int argc)
{
	*flag = ft_strdup(argv[*i]);
	if (ft_strcmp(*flag, "-dump") == 0)
	{
		if (argc >= 3)
		{
			free(*flag);
			*i += 1;
			*flag = ft_strdup(argv[*i]);
			nb = ft_long_atoi(*flag);
			*dump = nb % 4294967296;
			*i += 1;
			free(*flag);
		}
	}
	else
		free(*flag);
}

int		check_dump(char **argv, int argc, unsigned int *dump, int *i)
{
	size_t		len;
	char		*flag;
	long long	nb;

	nb = 0;
	len = ft_strlen(argv[*i]);
	if (len > 5)
		check_dump2(argv, &flag, i, nb, dump, len);
	else if (len == 5)
		check_dump3(argv, &flag, i, nb, dump, argc);
	return (1);
}

int		check_number2(char **argv, char **flag, int *j, long long nb, size_t len)
{
	*flag = ft_strndup(argv[*j], 0, 2);
	if (ft_strcmp(*flag, "-n ") == 0)
	{
		free(*flag);
		*flag = ft_strndup(argv[*j], 3, len);
		ft_printf("%s\n", *flag);
		nb = ft_long_atoi(*flag);
		*j += 1;
		free(*flag);
		if (nb <= 0 || nb > INT_MAX)
			return (0);
	}
	else
		free(*flag);
	return (1);
}

int		check_number(int argc, char **argv, int *j)
{
	size_t		len;
	char		*flag;
	long long	nb;

	nb = 0;
	len = ft_strlen(argv[*j]);
	if (len > 2)
	{
		if (!(check_number2(argv, &flag, j, nb, len)))
			return (0);
	}
	else if (len == 2)
	{
		flag = ft_strdup(argv[*j]);
		if (ft_strcmp(flag, "-n") == 0)
		{
			if (argc > *j + 1)
			{
				free(flag);
				*j += 1;
				flag = ft_strdup(argv[*j]);
				nb = ft_long_atoi(flag);
				*j += 1;
				free(flag);
				if (nb <= 0 || nb > INT_MAX)
					return (0);
			}
		}
		else
			free(flag);
	}
	return (1);
}

int		check_display(char **argv, int argc, int *display, int *i)
{
	char		*flag;

	if (ft_strlen(argv[*i]) == 2)
	{
		flag = ft_strdup(argv[*i]);
		if (ft_strcmp(flag, "-v") == 0)
		{
			if (argc >= 3)
			{
				free(flag);
				*i += 1;
				*display = 1;
			}
		}
		else
			free(flag);
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
			ft_printf("Error: File %s is too small to be a champion\n"\
					, argv[j]);
			return (0);
		}
		else
			(*nb_player)++;
		if (*nb_player > MAX_PLAYERS)
		{
			ft_printf("Too many champions\n");
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
