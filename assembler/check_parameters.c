/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:36:41 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/11 13:36:51 by nkamolba         ###   ########.fr       */
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

int		check_param_num(char **arr, int param_num, t_inst *inst)
{
	int 	i;

	i = 0;
	while (arr[i])
		i++;
	if (param_num == i)
	{
		inst->param_num = param_num;
		inst->param_arr = arr;
		return (1);
	}
	return (0);
}

void	get_inst_len(t_op *op, t_inst *inst, char type)
{
	if (type & T_REG)
		inst->len++;
	else if (type & T_DIR)
		inst->len += op->direct_len;
	else if (type & T_IND)
		inst->len += 2;
}

void	check_parameters(char *str, t_op *op, t_inst *inst, int line_nb)
{
	char	**arr;
	char	type;
	int		i;

	if (!(arr = ft_strsplit(str, SEPARATOR_CHAR)))
		ft_error_line("ft_strsplit failed in check_parameters", line_nb);
	if (!check_param_num(arr, op->param_num, inst))
		ft_error_line("parameter number is wrong", line_nb);
	i = 0;
	while (arr[i])
	{
		if (!(type = get_param_type(arr[i], inst, i)))
			ft_error_line("arguments have wrong format", line_nb);
		if (!(type & op->param_type[i]))
			ft_error_line("input arguments have wrong type", line_nb);
		get_inst_len(op, inst, type);
		if (type & T_REG)
			check_registry(arr[i], line_nb);
		else if (type & T_LAB)
			check_label(arr[i], type, line_nb);
		else if (type & (T_DIR | T_IND))
			check_number(arr[i], type, line_nb);
		i++;
		
	}
}
