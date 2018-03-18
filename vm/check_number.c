/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:21:40 by arobion           #+#    #+#             */
/*   Updated: 2018/03/17 15:48:21 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_number2(char **argv, char **flag, int *j, t_norme opt)
{
	if (!(*flag = ft_strndup(argv[*j], 0, 2)))
		exit(0);
	if (ft_strcmp(*flag, "-n ") == 0)
	{
		ft_strdel(flag);
		if (!(*flag = ft_strndup(argv[*j], 3, opt.len)))
			exit(0);
		opt.nb = ft_long_atoi(*flag);
		*j += 1;
		ft_strdel(flag);
		if (opt.nb <= 0 || opt.nb > INT_MAX)
			return (0);
	}
	else
		ft_strdel(flag);
	return (1);
}

int		check_number3(char **argv, char **flag, int *j, t_norme opt)
{
	if (!(*flag = ft_strdup(argv[*j])))
		exit(0);
	if (ft_strcmp(*flag, "-n") == 0)
	{
		if (opt.argc > *j + 1)
		{
			ft_strdel(flag);
			*j += 1;
			if (!(*flag = ft_strdup(argv[*j])))
				exit(0);
			opt.nb = ft_long_atoi(*flag);
			*j += 1;
			ft_strdel(flag);
			if (opt.nb <= 0 || opt.nb > INT_MAX)
				return (0);
		}
		else
			ft_strdel(flag);
	}
	else
		ft_strdel(flag);
	return (1);
}

int		check_number(int argc, char **argv, int *j)
{
	char		*flag;
	t_norme		opt;

	opt.nb = 0;
	opt.len = ft_strlen(argv[*j]);
	opt.argc = argc;
	if (opt.len > 2)
	{
		if (!(check_number2(argv, &flag, j, opt)))
			return (0);
	}
	else if (opt.len == 2)
		if (!(check_number3(argv, &flag, j, opt)))
			return (0);
	return (1);
}
