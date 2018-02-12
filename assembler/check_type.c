/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 18:34:48 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/12 18:37:08 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	check_registry(char *str, int line_nb)
{
	int		num;

	str++;
	if (!ft_isdigit(*str) || *str == '0')
		ft_error_line("registry argument has wrong format", line_nb);
	num = ft_atoi(str);
	if (num < 1 || num > REG_NUMBER)
		ft_error_line("registry argument is out of the limit", line_nb);
	while (ft_isdigit(*str))
		str++;
	if (*str != '\0')
		ft_error_line("registry argument has wrong format", line_nb);
}

static void	check_number(char *str, char type, int line_nb)
{
	if (type & T_DIR)
		str++;
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			ft_error_line("number argument has wrong format", line_nb);
		str++;
	}
}

static void	check_label(char *str, char type, int line_nb)
{
	if (type & T_DIR)
		str++;
	str++;
	if (*str == 0)
		ft_error_line("no character after label char", line_nb);
	while (*str)
	{
		if (!ft_strchr(LABEL_CHARS, *str))
			ft_error_line("label argument has wrong format", line_nb);
		str++;
	}
}

void		check_type(char *str, int type, int line_nb)
{
	if (type & T_REG)
		check_registry(str, line_nb);
	else if (type & T_LAB)
		check_label(str, type, line_nb);
	else if (type & (T_DIR | T_IND))
		check_number(str, type, line_nb);
}
