/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_champs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:35:23 by arobion           #+#    #+#             */
/*   Updated: 2018/02/15 12:14:06 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		print_error_max_size(int p, int save, char *champ)
{
	ft_printf("Error: File %s has too large a code (%d bytes > %d bytes)\n"\
			, champ, p - save, CHAMP_MAX_SIZE);
	return (0);
}

int		load_one_champ(t_arena arn, char *champ, int p, int fd)
{
	char	*l;
	int		i;
	int		save;

	i = 0;
	save = p;
	if (!(l = ft_strnew(1)))
		exit(0);
	while (read(fd, l, 1))
	{
		i++;
		if (i > PROG_NAME_LENGTH + COMMENT_LENGTH + 16)
		{
			arn.mem[p] = l[0];
			p++;
		}
	}
	free(l);
	if (p - save > CHAMP_MAX_SIZE)
		return (print_error_max_size(p, save, champ));
	return (1);
}

int		start_of_input(int i, int nb_players)
{
	int		sizeof_one_player;
	int		ret;

	sizeof_one_player = MEM_SIZE / nb_players;
	ret = (i - 1) * sizeof_one_player;
	return (ret);
}

int		load_champs(t_arena arn, char **argv, int nb_players)
{
	int		i;
	int		fd;

	i = 1;
	while (i <= nb_players)
	{
		fd = open(argv[i], O_RDONLY);
		if (!(load_one_champ(arn, argv[i], start_of_input(i, nb_players), fd)))
			return (0);
		close(fd);
		i++;
	}
	return (1);
}
