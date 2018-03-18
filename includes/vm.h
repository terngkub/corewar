/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:19:19 by arobion           #+#    #+#             */
/*   Updated: 2018/03/17 14:38:17 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/ft_printf.h"
# include <ncurses.h>
# include <limits.h>

# define COLOR_LGREY	10
# define COLOR_NRED		11
# define COLOR_TRED		12
# define COLOR_LBLUE	13
# define COLOR_LGREEN	14
# define COLOR_WGREEN	15
# define COLOR_LYELLOW	16

typedef struct			s_norme
{
	int					i;
	int					j;
	int					fd;
	int					argc;
	int					start;
	unsigned int		dump;
	int					display;
	size_t				len;
	long long			nb;
}						t_norme;

typedef struct			s_process
{
	char				alive;
	char				**regs;
	int					opc;
	int					cycle_to_wait;
	int					pc;
	int					carry;
	int					color;
	struct s_op			*op;
	struct s_process	*next;
}						t_process;

typedef struct			s_player
{
	int					number;
	char				*name;
	char				*comment;
	int					nb_live;
	int					last_live;
}						t_player;

typedef struct			s_arena
{
	char				*mem;
	char				*color;
	int					lives;
	int					winner;
	int					nb_cycle;
	int					nb_players;
	int					displays;
	t_player			*players;
	int					nb_checks;
	t_process			*process;
}						t_arena;

typedef struct			s_op
{
	char				*instruction;
	char				param_num;
	char				param_type[3];
	char				opcode;
	int					cycle;
	char				*name;
	char				ocp;
	char				carry;
	char				direct_len;
}						t_op;

typedef struct			s_visu
{
	WINDOW				*arena;
	WINDOW				*info;
	WINDOW				*background;
	WINDOW				*man;
	int					next_cycle_to_die;
	int					cycle_to_die;
	int					proc;
}						t_visu;

int						check_number(int argc, char **argv, int *j);
int						parse_champs(int argc, char **argv, t_norme *opt);
int						load_champs(t_arena arn, char **argv,\
		int nb_players, t_norme opt);
int						check_champ_size(int fd, char *header, char *l);
int						check_magic(char *header, char *l);
int						check_header(int fd, char *l);
int						start_of_input(int i, int nb_players);
int						opc_nb_cycle(int opc);
void					ft_fork_front(t_process **begin_list,\
		t_process *curr, t_arena *arn, int new_pc);
t_process				*cpy_process(t_process *curr, t_arena *arn, int new_pc);
void					cpy_regs(t_process *curr, t_process *lst);
int						modif_pc(unsigned char ocp);
int						valid_ocp(unsigned char ocp);
int						check_dump(char **argv, int argc,\
		unsigned int *dump, int *i);
int						check_number(int argc, char **argv, int *j);

int						init_arena(t_arena *arn, int nb_players,\
		char **argv, t_norme opt);
int						init_players(t_player *players, int nb_players,\
		char **argv, int i);
int						get_number(char **argv, int *j);
t_player				create_one_player(char *champ, int number);
void					init_process(t_arena arn, t_process **begin_list);

void					run_cycle(t_arena *arn, int dump, int display);
void					kill_and_refresh_processes(t_arena *arn, t_process\
		**begin_list, int *next, int *die);
int						nb_of_process(t_process **begin_list);
int						free_mem_err(t_arena arn);
int						free_arena_err(t_arena arn);
void					freeall(t_arena *arn);
void					free_one_process(t_process **process);

void					print_registry(char **regs);
int						print_no_file(char *str);
void					print_mem(char *mem, int size);
void					dump_mem(t_arena arn);
void					print_arena(t_arena arn);
int						write_usage(void);

int						hex_to_dec(char *str, int len);
int						x_char_to_int(char *str, int len);
void					int_to_x_char(char *str, int len, int value);

t_op					*get_op(int opc);

int						check_param_type(t_arena *arn, t_process *process,
		char type[3]);
int						get_fail_pos(t_process *process, char type[3]);
int						handle_idx(int value);

int						read_mem(t_arena *arn, int index, int len);
int						check_get_registry(t_process *process, char\
		type[3], int *param, int len);
int						get_registry(t_arena *arn, t_process *process, int pos);
int						get_direct_2(t_arena *arn, t_process *process,\
		int pos, int l);
int						get_direct_4(t_arena *arn, t_process *process, int pos);
int						get_indirect(t_arena *arn, t_process *process,\
		int pos, int l);

void					set_registry(char *registry, int value);
void					set_mem(t_arena *arn, int index, int value, int color);

void					live(t_arena *arena, t_process *process);
void					ld(t_arena *arn, t_process *process, int l);
void					ldi(t_arena *arn, t_process *process, int l);
void					lld(t_arena *arn, t_process *process);
int						st(t_arena *arn, t_process *process);
void					sti(t_arena *arn, t_process *process);
void					add(t_arena *arn, t_process *process);
void					sub(t_arena *arn, t_process *process);
void					bitwise(t_arena *arn, t_process *process, char op);
void					zjmp(t_arena *arn, t_process *process);
void					ft_fork(t_arena *arn, t_process *process, int l);
void					long_fork(t_arena *arn, t_process *process);
void					aff(t_arena *arn, t_process *process);

int						ft_visu(t_arena *arn);
int						nb_of_process(t_process **begin_list);
void					run_processes(t_arena *arn);
void					kill_and_refresh_processes(t_arena *arn,\
		t_process **begin_list, int *next, int *die);
void					set_color_process(char *color, t_process *begin_list);
void					game(t_visu *v, t_arena *arn);
void					refresh_color_process(char *str);
void					put_arena(t_visu v, const char *mem, const char *color);
void					f_p(char *byte, char mem);
void					put_man(t_visu *v);
int						free_visu(t_visu *v);
void					set_color(t_visu v, char c);
void					put_winner(t_arena *arn, t_visu *v);
void					put_info(t_visu v, t_arena *arn, int win, int run);
void					put_title(t_visu *v);
void					set_colorx(void);
void					put_win(t_visu v, t_arena *arn, int win);
void					put_onebyone(t_visu v);
void					put_pause(t_visu v);
void					put_running(t_visu v);

#endif
