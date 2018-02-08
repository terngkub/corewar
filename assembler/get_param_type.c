/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:16:11 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/08 16:16:55 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char	get_param_type(char *str)
{
	if (str[0] == 'r')
		return (T_REG);
	else if (str[0] == '%')
	{
		if (ft_isdigit(str[1]))
			return (T_DIR);
		else if (str[1] == ':')
			return (T_DIR | T_LAB);
		return (0);
	}
	else if (ft_isdigit(str[0]))
		return (T_IND);
	else if (str[0] == ':')
		return (T_IND | T_LAB);
	return (0);
}
