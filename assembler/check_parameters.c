/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:36:41 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/06 18:17:49 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../includes/asm.h"
#include "../includes/op.h"

void	ft_error(char *str);

char	*ft_remove_space(char *str)
{
	int		new_len;
	int		i;
	int		j;
	char	*new_str;

	new_len = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			new_len++;
		i++;
	}
	if (!(new_str = ft_strnew(new_len)))
		ft_error("");
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			new_str[j++] = str[i];
		i++;
	}
	ft_printf("%s\n", new_str);
	return (new_str);
}

void	check_registry(char *str)
{
	int		num;

	ft_printf("check_registry %s\n", str);
	str++;
	if (!ft_isdigit(*str) || *str == '0')
		ft_error("");
	num = ft_atoi(str);
	if (num < 1 || num > REG_NUMBER)
		ft_error("");
	while (ft_isdigit(*str))
		str++;
	if (*str != '\0')
		ft_error("");
}

void	check_number(char *str, char type)
{
	ft_printf("check_number %s\n", str);
	if (type == 'd')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			ft_error("");
		str++;
	}
}

void	check_label(char *str, char type)
{
	ft_printf("check_label %s\n", str);
	if (type == 'D')
		str += 2;
	if (type == 'I')
		str++;
	while (*str)
	{
		if (!ft_strchr(LABEL_CHARS, *str))
			ft_error("");
		str++;
	}
}

char	get_type(char *str)
{
	if (str[0] == 'r')
		return ('r');
	else if (str[0] == '%')
	{
		if (ft_isdigit(str[1]))
			return ('d');
		else if (str[1] == ':')
			return ('D');
		ft_error("");
	}
	else if (ft_isdigit(str[0]))
		return ('i');
	else if (str[0] == ':')
		return ('I');
	ft_error("");
	return (0);
}

void	check_parameters(char *str)
{
	char	**arr;
	char	type;
	int		i;

	arr = ft_strsplit(str, SEPARATOR_CHAR);
	i = 0;
	while (arr[i])
	{
		ft_printf("loop %d: ", i);
		if (!(type = get_type(arr[i])))
			ft_error("");
		if (type == 'r')
			check_registry(arr[i]);
		if (type == 'd' || type == 'i')
			check_number(arr[i], type);
		if (type == 'D' || type == 'I')
			check_label(arr[i], type);
		i++;
	}
}

int		main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	check_parameters(ft_remove_space(argv[1]));
	ft_printf("valid\n");
	return (0);
}
