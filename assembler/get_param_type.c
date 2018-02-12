/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:16:11 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/12 18:31:11 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	get_param_byte(t_inst *inst, int i, int value)
{
	if (i == 0)
		inst->param_byte = value * 64;
	else if (i == 1)
		inst->param_byte += value * 16;
	else
		inst->param_byte += value * 4;
}

char		get_param_type(char *str, t_inst *inst, int i)
{
	if (str[0] == 'r')
	{
		get_param_byte(inst, i, 1);
		return (T_REG);
	}
	if (str[0] == '%')
	{
		get_param_byte(inst, i, 2);
		if (ft_isdigit(str[1]) || str[1] == '-')
			return (T_DIR);
		else if (str[1] == ':')
			return (T_DIR | T_LAB);
		return (0);
	}
	get_param_byte(inst, i, 3);
	if (ft_isdigit(str[0]) || str[0] == '-')
		return (T_IND);
	else if (str[0] == ':')
		return (T_IND | T_LAB);
	return (0);
}
