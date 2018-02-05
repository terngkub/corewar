/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:36:41 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/05 22:00:14 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int		check_registry(char *str)
{
	int		num;

	str++;
	if (!isdigit(*str) || *str == '0')
		return (0);
	num = atoi(str);
	if (num < 1 || num > 16)
		return (0);
	str = num > 9 ? str + 2 : str + 1;
	if (*str != '\0')
		return (0);
	return (1);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	printf("%d\n", check_registry(argv[1]));
	return (0);
}
