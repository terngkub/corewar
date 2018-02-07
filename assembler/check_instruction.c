/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:33:17 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/07 21:25:03 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	check_label_infront(char *str, int start, int end)
{
	int		i;

	i = start;
	while (i < end)
	{
		if (!ft_strchr(LABEL_CHARS, str[i]))
			ft_error("label name contains non LABEL_CHARS");
		i++;
	}
}

void	check_instruction(char *str)
{
	char	*line;
	int		i;

	ft_trim(&str);
	while (str[i] && !ft_isspace(str[i]))
	{
		if (str[i] == LABEL_CHAR)
		{
			check_label_infront(str, 0, i);
			break;
		}
		i++;
	}
	//get string until space
	//check command
	//check parameter
	ft_printf("valid\n");
}

int		main(void)
{
	char	*str = "    testT:   sti";

	check_instruction(str);
	return (0);
}
