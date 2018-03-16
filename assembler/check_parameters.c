/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:36:41 by nkamolba          #+#    #+#             */
/*   Updated: 2018/03/16 16:38:28 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	check_param_num(char *str, char **arr, int param_num, int line_nb)
{
	int		i;
	int		sep_num;
	int		arr_num;

	i = 0;
	sep_num = 0;
	while (str[i])
		if (str[i++] == SEPARATOR_CHAR)
			sep_num++;
	arr_num = 0;
	while (arr[arr_num])
		arr_num++;
	if (arr_num != sep_num + 1)
		ft_error_line("too much separators", line_nb);
	if (param_num != arr_num)
		ft_error_line("parameter number is wrong", line_nb);
}

static void	get_inst_len(t_op *op, t_inst *inst, char type)
{
	if (type & T_REG)
		inst->len++;
	else if (type & T_DIR)
		inst->len += op->direct_len;
	else if (type & T_IND)
		inst->len += 2;
}

void		check_parameters(char *str, t_op *op, t_inst *inst, int line_nb)
{
	char	**arr;
	char	*tmp;
	char	type;
	int		i;

	if (!(arr = ft_strsplit(str, SEPARATOR_CHAR)))
		ft_error_line("ft_strsplit failed in check_parameters", line_nb);
	check_param_num(str, arr, op->param_num, line_nb);
	i = -1;
	while (++i < op->param_num)
	{
		if (!(tmp = ft_strtrim(arr[i])))
			ft_error_line("ft_strtrim failed in check_parameters", line_nb);
		ft_strdel(&arr[i]);
		arr[i] = tmp;
		if (!(type = get_param_type(arr[i], inst, i)))
			ft_error_line("ft_strtrim failed in check_parameters", line_nb);
		if (!(type & op->param_type[i]))
			ft_error_line("input arguments have wrong type", line_nb);
		check_type(arr[i], type, line_nb);
		get_inst_len(op, inst, type);
		inst->param_num = op->param_num;
		inst->param_arr = arr;
	}
}
