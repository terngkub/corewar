/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:19:56 by arobion           #+#    #+#             */
/*   Updated: 2018/03/16 18:20:08 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	check_dump2(char **argv, char **flag, int *i, t_norme *opt)
{
	*flag = ft_strndup(argv[*i], 0, 4);
	if (ft_strcmp(*flag, "-dump") == 0)
	{
		ft_strdel(flag);
		*flag = ft_strndup(argv[*i], 5, opt->len);
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
	*flag = ft_strdup(argv[*i]);
	if (ft_strcmp(*flag, "-dump") == 0)
	{
		if (opt->argc >= 3)
		{
			ft_strdel(flag);
			*i += 1;
			*flag = ft_strdup(argv[*i]);
			opt->nb = ft_long_atoi(*flag);
			opt->dump = opt->nb % 4294967296;
			*i += 1;
			ft_strdel(flag);
		}
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
