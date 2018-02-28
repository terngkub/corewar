/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:07:55 by arobion           #+#    #+#             */
/*   Updated: 2018/02/28 12:11:09 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		get_number2(char **argv, char **flag, int *j, t_norme opt)
{
	*flag = ft_strndup(argv[*j], 0, 2);
	if (ft_strcmp(*flag, "-n ") == 0)
	{
		free(*flag);
		*flag = ft_strndup(argv[*j], 3, opt.len);
		ft_printf("%s\n", *flag);
		opt.nb = ft_long_atoi(*flag);
		*j += 1;
		free(*flag);
	}
	else
		free(*flag);
}

int			get_number(char **argv, int *j)
{
	char		*flag;
	t_norme		opt;

	opt.nb = 0;
	opt.len = ft_strlen(argv[*j]);
	if (opt.len > 2)
		get_number2(argv, &flag, j, opt);
	else if (opt.len == 2)
	{
		flag = ft_strdup(argv[*j]);
		if (ft_strcmp(flag, "-n") == 0)
		{
			free(flag);
			*j += 1;
			flag = ft_strdup(argv[*j]);
			opt.nb = ft_long_atoi(flag);
			*j += 1;
			free(flag);
		}
		else
			free(flag);
	}
	return (opt.nb);
}

void		create_name(int fd, char *name, char *l)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < 4)
		read(fd, l, 1);
	while (i < 4 + PROG_NAME_LENGTH)
	{
		read(fd, l, 1);
		name[j++] = l[0];
		i++;
	}
}

void		create_comment(int fd, char *comment, char *l)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < 8)
		read(fd, l, 1);
	while (i < 8 + COMMENT_LENGTH)
	{
		read(fd, l, 1);
		comment[j++] = l[0];
		i++;
	}
}

t_player	create_one_player(char *champ, int number)
{
	t_player	player;
	int			fd;
	char		*l;

	if (!(l = ft_strnew(1)))
		exit(0);
	if (!(player.name = ft_strnew(PROG_NAME_LENGTH)))
		exit(0);
	if (!(player.comment = ft_strnew(COMMENT_LENGTH)))
		exit(0);
	fd = open(champ, O_RDONLY);
	create_name(fd, player.name, l);
	create_comment(fd, player.comment, l);
	player.number = number;
	player.nb_live = 0;
	player.last_live = 0;
	free(l);
	close(fd);
	return (player);
}
