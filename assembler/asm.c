/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:15:02 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/10 15:39:17 by fbabin           ###   ########.fr       */
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
	while (size)
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

int			check_champion_integrity(t_champ *champ, t_check *check)
{
	if (check->name == 0)
		return (ft_error_return("champion has no name", 0));
	if (check->comment == 0)
		return (ft_error_return("champion has no comment", 0));
	if (!champ->labels || !champ->inst)
		return (ft_error_return("champion has no instruction", 0));
	return (1);
}

void		ft_initcheck(t_check *check)
{
	check->name = 0;
	check->comment = 0;
}

int			main(int argc, char **argv)
{
	int			fd_read;
	int			fd_write;
	char		*cor_filename;
	char		*line;
	int			line_nb;
	t_champ		champ;
	t_check		check;

	ft_initchamp(&champ);
	ft_initcheck(&check);
	line_nb = 0;
	if (argc != 2 || !check_file_name(argv[1]))
		ft_error("wrong input");
	fd_read = open(argv[1], O_RDONLY);
	cor_filename = get_cor_name(argv[1]);
	fd_write = open(cor_filename, O_WRONLY | O_CREAT, 0755);
	while (sget_next_line(fd_read, &line) > 0)
	{
		line_nb++;
		if (line[0] == COMMENT_CHAR)
			continue ;
		else if (!ft_strncmp(line, NAME_CMD_STRING, 5))
		{
			if (check_name(&champ, line, line_nb, &check))
				continue ;
			else
				return (-1);
		}
		else if (!ft_strncmp(line, COMMENT_CMD_STRING, 7))
		{
			if (check_comment(&champ, line, line_nb, &check))
				continue ;
			else
				return (-1);
		}
		else if (!check_instruction_line(&champ, line, line_nb))
			return (-1);
		free(line);
	}
	if (!(check_champion_integrity(&champ, &check)))
		return (-1);
	write_champion(fd_write, &champ);
	//print_inst_list(champ.inst);
	//print_labels_list(champ.labels);
	close(fd_read);
	close(fd_write);
	return (0);
}
