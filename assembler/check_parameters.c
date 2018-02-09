/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:36:41 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/09 14:39:29 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	check_registry(char *str)
{
	int		num;

	str++;
	if (!ft_isdigit(*str) || *str == '0')
		ft_error("registry argument has wrong format");
	num = ft_atoi(str);
	if (num < 1 || num > REG_NUMBER)
		ft_error("registry argument is out of the limit");
	while (ft_isdigit(*str))
		str++;
	if (*str != '\0')
		ft_error("registry argument has wrong format");
}

static void	check_number(char *str, char type)
{
	if (type & T_DIR)
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			ft_error("number argument has wrong format");
		str++;
	}
}

static void	check_label(char *str, char type)
{
	if (type & T_DIR)
		str++;
	str++;
	while (*str)
	{
		if (!ft_strchr(LABEL_CHARS, *str))
			ft_error("label argument has wrong format");
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

void	check_parameters(char *str, t_op *op, t_inst *inst)
{
	char	**arr;
	char	type;
	int		i;

	if (!(arr = ft_strsplit(str, SEPARATOR_CHAR)))
		ft_error("ft_strsplit failed in check_parameters");
	if (!check_param_num(arr, op->param_num, inst))
		ft_error("parameter number is wrong");
	i = 0;
	while (arr[i])
	{
		if (!(type = get_param_type(arr[i], inst, i)))
			ft_error("arguments have wrong format");
		if (!(type & op->param_type[i]))
			ft_error("input arguments have wrong type");
		get_inst_len(op, inst, type);
		if (type & T_REG)
			check_registry(arr[i]);
		else if (type & T_LAB)
			check_label(arr[i], type);
		else if (type & (T_DIR | T_IND))
			check_number(arr[i], type);
		i++;
		
	}
}
