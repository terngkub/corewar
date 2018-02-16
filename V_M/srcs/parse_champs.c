/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:32:42 by arobion           #+#    #+#             */
/*   Updated: 2018/02/16 16:45:38 by arobion          ###   ########.fr       */
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

int		check_dump(char **argv, int argc, unsigned int *dump, int *i)
{
	size_t		len;
	char		*flag;
	long long	nb;

	len = ft_strlen(argv[*i]);
	if (len > 5)
	{
		flag = ft_strndup(argv[*i], 0, 4);
		if (ft_strcmp(flag, "-dump") == 0)
		{
			free(flag);
			flag = ft_strndup(argv[*i], 5, len);
			nb = ft_long_atoi(flag);
			*dump = nb % 4294967296;
			*i += 1;
			free(flag);
		}
		else
			free(flag);
	}
	else if (len == 5)
	{
		flag = ft_strdup(argv[*i]);
		if (ft_strcmp(flag, "-dump") == 0)
		{
			if (argc >= 3)
			{
				free(flag);
				*i += 1;
				flag = ft_strdup(argv[*i]);
				nb = ft_long_atoi(flag);
				*dump = nb % 4294967296;
				*i += 1;
				free(flag);
			}
		}
		else
			free(flag);
	}
	return (1);
}

int		check_number(int argc, char **argv, int *j)
{
	size_t		len;
	char		*flag;
	long long	nb;

	len	 = ft_strlen(argv[*j]);
	if (len > 2)
	{
		flag = ft_strndup(argv[*j], 0, 2);
		if (ft_strcmp(flag, "-n ") == 0)
		{
			free(flag);
			flag = ft_strndup(argv[*j], 3, len);
			ft_printf("%s\n", flag);
			nb = ft_long_atoi(flag);
			*j += 1;
			free(flag);
			if (nb <= 0 || nb > INT_MAX)
				return (0);
		}
		else
			free(flag);
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

int		parse_champs(int argc, char **argv, int *i, unsigned int *dump)
{
	int		j;
	int		nb_player;

	nb_player = 0;
	if (argc <= 1)
		return (write_usage());
	if (!(check_dump(argv, argc, dump, i)) || *i >= argc)
		return (write_usage());
	j = *i;
	while (j < argc)
	{
		if (!(check_number(argc, argv, &j)) || j >= argc)
			return(write_usage());
		if (ft_checkfile(argv[j]) == 0)
			return (print_no_file(argv[j]));
		if (ft_checkname(argv[j]) == 0)
		{
			ft_printf("Error: File %s is too small to be a champion\n"\
					, argv[j]);
			return (0);
		}
		else
			nb_player++;
		if (nb_player > MAX_PLAYERS)
		{
			ft_printf("Too many champions\n");
			return (0);
		}
		j++;
	}
	return (nb_player);
}
