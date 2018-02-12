/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:19:19 by arobion           #+#    #+#             */
/*   Updated: 2018/02/12 18:47:19 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../includes/op.h"
# include "../libft/includes/libft.h"	
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/ft_printf.h"

typedef struct			s_process
{
	int					opc;
	int					cycle_to_wait;
	int					pc_instr;
	struct s_process	*next;
}						t_process;

typedef struct			s_arena
{
	int			nb_cycle;
	int			nb_live_1;
	int			nb_live_2;
	int			last_live_1;
	int			last_live_2;
	int			carry;
	int			pc_1;
	int			pc_2;
	char		*mem;
	t_process	*process;
}						t_arena;

#endif
