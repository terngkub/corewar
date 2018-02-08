/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:33:17 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/08 16:32:28 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	skip_nonspace(char *str, int i)
{
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}

static int	skip_space(char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

static int	check_label_infront(char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		if (str[i] == LABEL_CHAR)
		{
			j = 0;
			while (j < i)
			{
				if (!ft_strchr(LABEL_CHARS, str[j]))
					ft_error("label name contains non-LABEL_CHARS");
				j++;
			}
			return (i + 1);
		}
		i++;
	}
	return (0);
}

static t_op	*check_instruction(char *str)
{
	int		instruction_len;
	char	*instruction;
	t_op	*op;

	instruction_len = 0;
	while (!ft_isspace(str[instruction_len]))
		instruction_len++;
	if (!(instruction = ft_strsub(str, 0, instruction_len)))
		ft_error("ft_strsub failed in check_instruction");
	if (!(op = get_op(instruction)))
		ft_error("instuction not found");
	free(instruction);
	return (op);
}

int		check_instruction_line(char *line)
{
	char	*str;
	char	*param;
	int		i;
	t_op	*op;

	if (!(str = ft_trim(line)))
		return (1);
	i = check_label_infront(str);
	if (!str[i])
		return (1);
	i = skip_space(str, i);
	op = check_instruction(&str[i]);
	i = skip_nonspace(str, i);
	i = skip_space(str, i);
	param = ft_remove_space(&str[i]);
	check_parameters(param, op);
	free(str);
	free(param);
	return (1);
}

/*
int		main(void)
{
	//valid
	ft_printf("%d\n", check_instruction_line("test:"));
	ft_printf("%d\n", check_instruction_line("sti r1,%:live,%1"));
	ft_printf("%d\n", check_instruction_line("test: sti r1,%:live,%1"));
	
	//error
	//ft_printf("%d\n", check_instruction_line("Test:"));
	//ft_printf("%d\n", check_instruction_line("test r1,%:live,%1"));
	ft_printf("%d\n", check_instruction_line("test: sti r1,%:live,1"));

	return (0);
}
*/
