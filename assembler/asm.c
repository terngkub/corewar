/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:15:02 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/12 17:08:03 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_cor_name(char *filename)
{
	int		len;
	char	*cor_filename;

	len = ft_strlen(filename);
	if (!(cor_filename = ft_strnew(len + 2)))
		ft_error("malloc failed");
	ft_strncpy(cor_filename, filename, len - 1);
	ft_strcat(cor_filename, "cor");
	return (cor_filename);
}

int		check_file_name(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (len > 2 && str[len - 2] == '.' && str[len - 1] == 's' && str[len] == 0)
		return (1);
	return (0);
}

void	ft_initchamp(t_champ *champ)
{
	ft_bzero(champ->name, PROG_NAME_LENGTH + 1);
	ft_bzero(champ->comment, COMMENT_LENGTH + 1);
	champ->accu_len = 0;
	champ->inst = NULL;
	champ->labels = NULL;
}

void	disp_hexlen(int fd, size_t size, int len)
{

	unsigned char	*tmp;
	int				i;

	i = len;
	if (!(tmp = (unsigned char*)ft_memalloc(i * sizeof(unsigned char))))
		return ;
	while (size && i > 0)
	{
		tmp[--i] = size % 256;
		size /= 256;
	}
	write (fd, tmp, len);
	free(tmp);
}

void	write_inst(int fd, t_inst *inst, t_list *label_list)
{
	int			i;
	int			begin;
	int			len;
	char		*label;
	char		*name;
	int			addr;
	t_list		*start;

	start = label_list;
	disp_hexlen(fd, inst->opcode, 1);
	if (inst->ocp)
		disp_hexlen(fd, inst->param_byte, 1);
	i = 0;
	while (i < inst->param_num)
	{
		if (inst->param_arr[i][0] == 'r')
			disp_hexlen(fd, ft_atoi(&inst->param_arr[i][1]), 1);
		else if (!ft_strchr(inst->param_arr[i], ':'))
		{
			if (inst->param_arr[i][0] == '%')
				disp_hexlen(fd, ft_atoi(&inst->param_arr[i][1]), inst->direct_len);
			else
				disp_hexlen(fd, ft_atoi(&inst->param_arr[i][0]), 2);
		}
		else
		{
			begin = inst->param_arr[i][0] == '%' ? 2 : 1;
			len = ft_strlen(inst->param_arr[i]) - begin;
			label = ft_strsub(inst->param_arr[i], begin, len);
			addr = -1;
			label_list = start;
			while (label_list)
			{
				name = ((t_label *)label_list->content)->name;
				if (ft_strcmp(label, name) == 0)
				{
					addr = ((t_label *)label_list->content)->addr;
					break;
				}
				label_list = label_list->next;
			}
			if (addr != -1)
			{
				if (inst->param_arr[i][0] == '%')
					disp_hexlen(fd, addr - inst->addr, inst->direct_len);
				else
					disp_hexlen(fd, addr - inst->addr, 2);
			}
			free(label);
		}
		i++;
	}
}

void	write_champion(int fd, t_champ *champ)
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

void		check_label(t_list *inst_list, t_list *labels_list)
{
	t_list		*labels_head;
	t_inst		*inst;
	t_label		*label;
	int			i;
	int			j;
	int			found;

	labels_head = labels_list;
	while (inst_list)
	{
		inst = (t_inst *)inst_list->content;
		i = 0;
		while (i < inst->param_num && ft_strchr(inst->param_arr[i], ':'))
		{
			j = ft_strchr(inst->param_arr[i], '%') ? 2 : 1;
			found = 0;
			labels_list = labels_head;
			while (labels_list)
			{
				label = (t_label *)labels_list->content;
				if (ft_strcmp(&inst->param_arr[i][j], label->name) == 0)
				{
					found = 1;
					break;
				}
				labels_list = labels_list->next;
			}
			if (found == 0)
				ft_error("can't find referenced label of the parameters");
			i++;
		}
		inst_list = inst_list->next;
	}
}

int			check_champion_integrity(t_champ *champ, t_check *check)
{
	if (check->name == 0)
		return (ft_error_return("champion has no name", 0));
	if (check->comment == 0)
		return (ft_error_return("champion has no comment", 0));
	if (!champ->inst)
		return (ft_error_return("champion has no instruction", 0));
	check_label(champ->inst, champ->labels);
	return (1);
}

void		ft_initcheck(t_check *check)
{
	check->name = 0;
	check->comment = 0;
}

void		ft_initfile(t_file *f)
{
	f->line_nb = 0;
	f->line = NULL;
	f->fd_read = 0;
	f->cor_filename = NULL;
	f->fd_write = 0;
}

int			main(int argc, char **argv)
{
	t_file			f;
	t_champ			champ;
	t_check			check;

	ft_initchamp(&champ);
	ft_initcheck(&check);
	ft_initfile(&f);
	if (argc != 2 || !check_file_name(argv[1]))
		ft_error("wrong input");
	f.fd_read = open(argv[1], O_RDONLY);
	f.cor_filename = get_cor_name(argv[1]);
	while (sget_next_line(f.fd_read, &f.line) > 0)
	{
		f.line_nb++;
		if (f.line[0] == COMMENT_CHAR || f.line[0] == ';')
			;
		else if (!ft_strncmp(f.line + ft_strspn(f.line, " \t"), NAME_CMD_STRING, 5))
			check_name(&champ, &f, &check);
		else if (!ft_strncmp(f.line + ft_strspn(f.line, " \t"), COMMENT_CMD_STRING, 7))
			check_comment(&champ, &f, &check);
		else if (!check_instruction_line(&champ, f.line, f.line_nb))
			return (free_return(&f, &champ, -1));
		free(f.line);
	}
	free(f.line);
	if (!(check_champion_integrity(&champ, &check)))
		return (-1);
	f.fd_write = open(f.cor_filename, O_WRONLY | O_CREAT, 0755);
	write_champion(f.fd_write, &champ);
	close(f.fd_read);
	close(f.fd_write);
	return (free_return(&f, &champ, 0));
}
