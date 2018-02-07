/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:36:41 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/07 18:21:53 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../includes/asm.h"
#include "../includes/op.h"

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

	ft_printf("%-14s %s\n", "check_registry", str);
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
	ft_printf("%-14s %s\n", "check_number", str);
	if (type & T_DIR)
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
	ft_printf("%-14s %s\n", "check_label", str);
	if (type & T_DIR)
		str += 2;
	else
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
		return (T_REG);
	else if (str[0] == '%')
	{
		if (ft_isdigit(str[1]))
			return (T_DIR);
		else if (str[1] == ':')
			return (T_DIR | T_LAB);
		ft_error("");
	}
	else if (ft_isdigit(str[0]))
		return (T_IND);
	else if (str[0] == ':')
		return (T_IND | T_LAB);
	return (0);
}

int		check_param_num(char **arr, int param_num)
{
	int 	i;
	int		len;

	i = 0;
	len = 0;
	while (arr[i++])
		len++;
	ft_printf("%-9s: %d\n", "param_num", param_num);
	ft_printf("%-9s: %d\n", "len", len);
	if (param_num == len)
		return (1);
	return (0);
}

void	check_parameters(char *instruction, char *str)
{
	t_op	*op;
	char	**arr;
	char	type;
	int		i;

	op = get_op(instruction);
	arr = ft_strsplit(str, SEPARATOR_CHAR);
	if (!check_param_num(arr, op->param_num))
		ft_error("parameter number is wrong");
	i = 0;
	while (arr[i])
	{
		ft_printf("loop %d ", i);
		if (!(type = get_type(arr[i])))
			ft_error("No type");
		ft_printf("type %2d ", (int)type);
		if (!(type & op->param_type[i]))
			ft_error("Wrong type");
		if (type & T_REG)
			check_registry(arr[i]);
		else if (type & T_LAB)
			check_label(arr[i], type);
		else if (type & (T_DIR | T_IND))
			check_number(arr[i], type);
		i++;
	}
}

/*int		main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	check_parameters(argv[1], ft_remove_space(argv[2]));
	ft_printf("valid\n");
	return (0);
}*/
