/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_champs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:35:23 by arobion           #+#    #+#             */
/*   Updated: 2018/03/09 16:37:53 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		print_error_max_size(int p, int save, char *champ)
{
	ft_dprintf(2, "Error: File %s has too large a code (%d bytes > %d bytes)\n"\
			, champ, p - save, CHAMP_MAX_SIZE);
	return (0);
}

int		check_magic(char *header)
{
	unsigned int	magic;
	
	magic = x_char_to_int(&header[0], 4);
	if (magic != COREWAR_EXEC_MAGIC)
		return (0);
	return (1);
}

int		check_champ_size(char *header)
{
	long long	ret;

	ret = x_char_to_int(&header[PROG_NAME_LENGTH + 4], 8);
	return (ret);
}

int		check_header(int fd, char *l)
{
	int		i;
	char	*header;
	int		ret;

	i = 0;
	if (!(header = ft_strnew(PROG_NAME_LENGTH + COMMENT_LENGTH + 16)))
			exit(0);
	while (i < PROG_NAME_LENGTH + COMMENT_LENGTH + 16)
	{
		read(fd, l, 1);
		header[i] = l[0];
		i++;
	}
	if (!(ret = check_magic(header)))
	{
		free(header);
		return (0);
	}
	if (!(ret = check_champ_size(header)))
	{
		free(header);
		return (0);
	}
	return (ret);
}

int		load_one_champ(t_arena arn, char *champ, int p, t_norme opt)
{
	char	*l;
	int		i;
	int		save;
	int		j;

	save = p;
	j = 0;
	if (!(l = ft_strnew(1)))
		exit(0);
	if (!(i = check_header(opt.fd, l)))
		return (0);
	while (j < i)
	{
			read(opt.fd, l, 1);
			arn.mem[j % MEM_SIZE] = l[0];
			arn.color[j % MEM_SIZE] = opt.j + 1;
			j++;
	}
	free(l);
	if (j - save > CHAMP_MAX_SIZE)
		return (print_error_max_size(j, save, champ));
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

int		load_champs(t_arena arn, char **argv, int nb_players, t_norme opt)
{
	int		index;

	index = opt.i;
	opt.j = 1;
	while (opt.j <= nb_players)
	{
		check_number(opt.argc, argv, &index);
		opt.fd = open(argv[index], O_RDONLY);
		if (!(load_one_champ(arn, argv[index],\
						start_of_input(opt.j, nb_players), opt)))
			return (0);
		close(opt.fd);
		(opt.j)++;
		index++;
	}
	return (1);
}
