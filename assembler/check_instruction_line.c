/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:33:17 by nkamolba          #+#    #+#             */
/*   Updated: 2018/03/16 16:37:15 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int		check_label_infront(char *str, t_champ *champ, int line_nb)
{
	int		i;
	int		j;
	t_label	*label;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		if (str[i] == LABEL_CHAR)
		{
			j = 0;
			while (j < i)
			{
				if (!ft_strchr(LABEL_CHARS, str[j++]))
					ft_error_line("label contains non-LABEL_CHARS", line_nb);
			}
			if (!(label = (t_label *)malloc(sizeof(t_label))))
				ft_error_line("failed to malloc label", line_nb);
			label->name = ft_strsub(str, 0, i);
			label->addr = champ->accu_len;
			ft_lstpushback(&champ->labels, label, sizeof(t_label));
			return (i + 1);
		}
		i++;
	}
	return (0);
}

static t_op		*check_instruction(char *str, int line_nb)
{
	int		instruction_len;
	char	*instruction;
	t_op	*op;

	instruction = NULL;
	instruction_len = 0;
	while (str[instruction_len] && !ft_isspace(str[instruction_len]))
		instruction_len++;
	if (!(instruction = ft_strsub(str, 0, instruction_len)))
		ft_error_line("ft_strsub failed in check_instruction", line_nb);
	if (!(op = get_op(instruction)))
		ft_error_line("instuction not found", line_nb);
	ft_strdel(&instruction);
	return (op);
}

static t_inst	*create_inst(t_champ *champ, t_op *op, int line_nb)
{
	t_inst	*inst;

	if (!(inst = (t_inst *)malloc(sizeof(t_inst))))
		ft_error_line("failed to malloc inst", line_nb);
	inst->opcode = op->opcode;
	inst->addr = champ->accu_len;
	inst->len = 1 + op->ocp;
	inst->ocp = op->ocp;
	inst->direct_len = op->direct_len;
	return (inst);
}

static void		remove_comment(char *str)
{
	int		i;

	i = ft_strchrindex(str, COMMENT_CHAR);
	if (i >= 0)
	{
		while (str[i])
			str[i++] = 0;
	}
}

int				check_instruction_line(t_champ *champ, char *line, int line_nb)
{
	char	*str;
	int		i;
	t_op	*op;
	t_inst	*inst;

	remove_comment(line);
	if (!(str = ft_strtrim(line)))
		return (1);
	i = check_label_infront(str, champ, line_nb);
	if (!str[i])
	{
		ft_strdel(&str);
		return (1);
	}
	i = skip_space(str, i);
	op = check_instruction(&str[i], line_nb);
	inst = create_inst(champ, op, line_nb);
	i = skip_nonspace(str, i);
	i = skip_space(str, i);
	check_parameters(&str[i], op, inst, line_nb);
	champ->accu_len += inst->len;
	ft_lstpushback(&champ->inst, inst, sizeof(t_inst));
	ft_strdel(&str);
	return (1);
}
