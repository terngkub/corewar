/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:21:40 by arobion           #+#    #+#             */
/*   Updated: 2018/03/03 16:24:00 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_number2(char **argv, char **flag, int *j, t_norme opt)
{
	*flag = ft_strndup(argv[*j], 0, 2);
	if (ft_strcmp(*flag, "-n ") == 0)
	{
		free(*flag);
		*flag = ft_strndup(argv[*j], 3, opt.len);
		opt.nb = ft_long_atoi(*flag);
		*j += 1;
		free(*flag);
		if (opt.nb <= 0 || opt.nb > INT_MAX)
			return (0);
	}
	else
		free(*flag);
	return (1);
}

int		check_number3(char **argv, char **flag, int *j, t_norme opt)
{
	*flag = ft_strdup(argv[*j]);
	if (ft_strcmp(*flag, "-n") == 0)
	{
		if (opt.argc > *j + 1)
		{
			free(*flag);
			*j += 1;
			*flag = ft_strdup(argv[*j]);
			opt.nb = ft_long_atoi(*flag);
			*j += 1;
			free(*flag);
			if (opt.nb <= 0 || opt.nb > INT_MAX)
				return (0);
		}
	}
	else
		free(*flag);
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
