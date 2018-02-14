/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:19:19 by arobion           #+#    #+#             */
/*   Updated: 2018/02/14 14:49:20 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../../includes/op.h"
# include "libft.h"	
# include "../../libft/includes/get_next_line.h"
# include "ft_printf.h"

typedef struct			s_process
{
	char				*regs;
	int					opc;
	int					cycle_to_wait;
	int					pc;
	int					carry;
	struct s_process	*next;
}						t_process;
/*
typedef struct			s_arena
{
	int			nb_cycle;
	int			nb_live_1;
	int			nb_live_2;
	int			last_live_1;
	int			last_live_2;
	char		*mem;
	t_process	*process;
}						t_arena;
*/
typedef struct			s_arena
{
	int			nb_cycle;
	t_list		*nb_lives;
	t_list		*last_lives;
	char		*mem;
	int			nb_checks;
	t_process	*process;
}

void	print_mem(char *mem, int size);
void	print_arena(t_arena arn);

#endif
