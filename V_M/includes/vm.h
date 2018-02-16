/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:19:19 by arobion           #+#    #+#             */
/*   Updated: 2018/02/16 16:44:29 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../../includes/op.h"
# include "libft.h"	
# include "../../libft/includes/get_next_line.h"
# include "ft_printf.h"

# define INT_MAX 2147483648

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


int						check_number(int argc, char **argv, int *j);
int						parse_champs(int argc, char **argv, int *i, unsigned int *dump);
int						load_champs(t_arena arn, char **argv, int nb_players, int i, int argc);
int						start_of_input(int i, int nb_players);
int						opc_nb_cycle(int opc);

int						init_arena(t_arena *arn, int nb_players, char **argv, int i, int argc);
int						init_players(t_player *players, int nb_players, char **argv, int i);
void					init_process(t_arena arn, t_process **begin_list);

void					run_cycle(t_arena *arn, int dump);

void					print_registry(char **regs);
void					print_mem(char *mem, int size);
void					dump_mem(t_arena arn);
void					print_arena(t_arena arn);
int						write_usage(void);

int						hex_to_dec(char *str, int len);
int						x_char_to_int(char *str, int len);
void					int_to_x_char(char *str, int len, int value);
t_player				*find_player(t_arena *arn, int number);

void					live(t_arena *arena, t_process *process);
void					ld(t_arena *arn, t_process *process);
void					aff(t_arena *arn, t_process *process);

#endif
