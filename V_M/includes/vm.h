/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:19:19 by arobion           #+#    #+#             */
/*   Updated: 2018/02/14 23:16:03 by nkamolba         ###   ########.fr       */
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
	char				alive;
	char				**regs;
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
typedef struct			s_player
{
	int			number;
	char		*name;
	char		*comment;
	int			nb_live;
	int			last_live;
}						t_player;

typedef struct			s_arena
{
	char		*mem;
	int			nb_cycle;
	int			nb_players;
	t_player	*players;
	int			nb_checks;
	t_process	*process;
}						t_arena;



int						parse_champs(int argc, char **argv);
int						load_champs(t_arena arn, char **argv, int nb_players);
int						start_of_input(int i, int nb_players);
int						opc_nb_cycle(int opc);

void					init_arena(t_arena *arn, int nb_players, char **argv);
void					init_players(t_player *players, int nb_players, char **argv);
void					init_process(t_arena arn, t_process **begin_list);

void					print_mem(char *mem, int size);
void					print_arena(t_arena arn);

void					live(t_arena *arena, t_process *process, int cycle);

#endif
