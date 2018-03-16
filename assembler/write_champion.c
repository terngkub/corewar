/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 20:07:14 by nkamolba          #+#    #+#             */
/*   Updated: 2018/03/16 16:41:34 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_number(int fd, t_inst *inst, int i)
{
	if (inst->param_arr[i][0] == '%')
		disp_hexlen(fd, ft_atoi(&inst->param_arr[i][1]), inst->direct_len);
	else
		disp_hexlen(fd, ft_atoi(&inst->param_arr[i][0]), 2);
}

static char	*get_label(t_inst *inst, int i)
{
	int			begin;
	int			len;
	char		*label;

	begin = inst->param_arr[i][0] == '%' ? 2 : 1;
	len = ft_strlen(inst->param_arr[i]) - begin;
	if (!(label = ft_strsub(inst->param_arr[i], begin, len)))
		ft_error("ft_strsub failed in get_label");
	return (label);
}

static void	write_label(int fd, t_inst *inst, t_list *label_list, int i)
{
	char		*label;
	char		*name;
	int			addr;
	int			direct_len;

	label = get_label(inst, i);
	addr = -1;
	while (label_list)
	{
		name = ((t_label *)label_list->content)->name;
		if (ft_strcmp(label, name) == 0)
		{
			addr = ((t_label *)label_list->content)->addr;
			break ;
		}
		label_list = label_list->next;
	}
	direct_len = inst->param_arr[i][0] == '%' ? inst->direct_len : 2;
	if (addr != -1)
		disp_hexlen(fd, addr - inst->addr, direct_len);
	else
		ft_error("can't find label");
	ft_strdel(&label);
}

static void	write_inst(int fd, t_inst *inst, t_list *label_list)
{
	int			i;

	disp_hexlen(fd, inst->opcode, 1);
	if (inst->ocp)
		disp_hexlen(fd, inst->param_byte, 1);
	i = 0;
	while (i < inst->param_num)
	{
		if (inst->param_arr[i][0] == 'r')
			disp_hexlen(fd, ft_atoi(&inst->param_arr[i][1]), 1);
		else if (!ft_strchr(inst->param_arr[i], ':'))
			write_number(fd, inst, i);
		else
			write_label(fd, inst, label_list, i);
		i++;
	}
}

void		write_champion(int fd, t_champ *champ)
{
	t_list		*t;

	disp_hexlen(fd, COREWAR_EXEC_MAGIC, 4);
	write(fd, champ->name, PROG_NAME_LENGTH);
	disp_hexlen(fd, champ->accu_len, 8);
	write(fd, champ->comment, COMMENT_LENGTH);
	write(fd, "\0\0\0\0", 4);
	t = champ->inst;
	while (t)
	{
		write_inst(fd, (t_inst *)t->content, champ->labels);
		t = t->next;
	}
}
