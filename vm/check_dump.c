/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:19:56 by arobion           #+#    #+#             */
/*   Updated: 2018/03/17 15:46:33 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	check_dump2(char **argv, char **flag, int *i, t_norme *opt)
{
	if (!(*flag = ft_strndup(argv[*i], 0, 4)))
		exit(0);
	if (ft_strcmp(*flag, "-dump") == 0)
	{
		ft_strdel(flag);
		if (!(*flag = ft_strndup(argv[*i], 5, opt->len)))
			exit(0);
		opt->nb = ft_long_atoi(*flag);
		opt->dump = opt->nb % 4294967296;
		*i += 1;
		ft_strdel(flag);
	}
	else
		ft_strdel(flag);
}

void	check_dump3(char **argv, char **flag, int *i, t_norme *opt)
{
	if (!(*flag = ft_strdup(argv[*i])))
		exit(0);
	if (ft_strcmp(*flag, "-dump") == 0)
	{
		if (opt->argc >= 3)
		{
			ft_strdel(flag);
			*i += 1;
			if (!(*flag = ft_strdup(argv[*i])))
				exit(0);
			opt->nb = ft_long_atoi(*flag);
			opt->dump = opt->nb % 4294967296;
			*i += 1;
			ft_strdel(flag);
		}
		ft_strdel(flag);
	}
	else
		ft_strdel(flag);
}

int		check_dump(char **argv, int argc, unsigned int *dump, int *i)
{
	char		*flag;
	t_norme		opt;

	opt.nb = 0;
	opt.len = ft_strlen(argv[*i]);
	opt.argc = argc;
	opt.dump = *dump;
	if (opt.len > 5)
		check_dump2(argv, &flag, i, &opt);
	else if (opt.len == 5)
		check_dump3(argv, &flag, i, &opt);
	*dump = opt.dump;
	return (1);
}
