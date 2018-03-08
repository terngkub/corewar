/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_champs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:35:23 by arobion           #+#    #+#             */
/*   Updated: 2018/03/03 16:13:02 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		print_error_max_size(int p, int save, char *champ)
{
	ft_dprintf(2, "Error: File %s has too large a code (%d bytes > %d bytes)\n"\
			, champ, p - save, CHAMP_MAX_SIZE);
	return (0);
}

int		load_one_champ(t_arena arn, char *champ, int p, t_norme opt)
{
	char	*l;
	int		i;
	int		save;

	i = 0;
	save = p;
	if (!(l = ft_strnew(1)))
		exit(0);
	while (read(opt.fd, l, 1))
	{
		i++;
		if (i > PROG_NAME_LENGTH + COMMENT_LENGTH + 16)
		{
			arn.mem[p % MEM_SIZE] = l[0];
			arn.color[p % MEM_SIZE] = opt.j + 1;
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