/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 18:40:36 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/08 20:39:48 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

/*
** --------------------------------- INCLUDES ---------------------------------
*/

# include "op.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/ft_printf.h"

/*
** -------------------------------- STRUCTURES --------------------------------
*/

typedef struct	s_champ
{
	char		name[PROG_NAME_LENGTH + 1];
	char		comment[COMMENT_LENGTH + 1];
	t_list		*inst;
	t_list		*labels;
}				t_champ;

typedef struct	s_op
{
	char		*instruction;
	char		param_num;
	char		param_type[3];
	char		opcode;
	int			cycle;
	char		*name;
	char		codebyte;
	char		carry;
}				t_op;

typedef struct	s_inst
{
	char		opcode;
	char		codebyte;
	int			param_byte;
	char		param_num;
	char		**param_arr;
}				t_inst;

typedef struct	s_label
{
	char		*name;
}				t_label;

/*
** ----------------------------------------------------------------------------
** ---------------------------------- SOURCES ---------------------------------
** ----------------------------------------------------------------------------
*/

t_op			*get_op(char *instruction);

void			ft_error(char *str);

char			*ft_trim(char *str);
char			*ft_remove_space(char *str);

void			print_inst_list(t_list *list);
void			print_labels_list(t_list *list);


/*
** ------------------------------ CHECK FUNCTIONS ------------------------------
*/

int			check_name(t_champ *champ, char *line, int line_nb);
int			check_comment(t_champ *champ, char *line, int line_nb);
int			check_instruction_line(t_champ *champ, char *line);
void		check_parameters(char *str, t_op *op, t_inst *inst);
char		get_param_type(char *str, t_inst *inst, int value);

#endif
