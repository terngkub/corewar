/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 18:40:36 by nkamolba          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/02/07 20:51:47 by nkamolba         ###   ########.fr       */
=======
/*   Updated: 2018/02/07 20:55:58 by fbabin           ###   ########.fr       */
>>>>>>> e1b0b543958d2d2474b6b267b81612b350c9fef7
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
	t_list		*instructions;
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

/*
** ----------------------------------------------------------------------------
** ---------------------------------- SOURCES ---------------------------------
** ----------------------------------------------------------------------------
*/

t_op			*get_op(char *instruction);
void			ft_error(char *str);
char			*ft_remove_space(char *str);

void			ft_trim(char **str);

/*
** ------------------------------ CHECK FUNCTIONS ------------------------------
*/

int			check_name(t_champ *champ, char *line, int line_nb);
int			check_comment(t_champ *champ, char *line, int line_nb);

#endif
