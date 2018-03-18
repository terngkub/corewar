# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/16 21:15:36 by fbabin            #+#    #+#              #
#    Updated: 2018/03/17 15:30:03 by fbabin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM				= asm
NAME			= corewar

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra

_ASM_SRCS		=	asm.c op.c init.c\
					check_name_comments.c \
					check_instruction_line.c skip.c \
					check_parameters.c get_param_type.c check_type.c \
					check_integrity.c \
					write_champion.c disp_hexlen.c \
					ft_error.c print_list.c \
					free.c \

_COREWAR_SRCS	=	main.c op.c visu.c displays.c parse_champs.c load_champs.c \
					init_arena.c init_players.c init_player2.c check_number.c \
					check_dump.c load_champ2.c \
					init_process.c run_cycle.c handle_process.c \
					freeall.c hex_to_dec.c modif_pc.c check_param_type.c \
					check_get_registry.c get.c set.c live.c ld.c lld.c \
					ldi.c st.c sti.c add.c sub.c bitwise.c zjmp.c fork.c \
					long_fork.c aff.c visu2.c visu3.c visu4.c put_mode.c \
					visu_game.c

_LIBFT			= libft.a
HEADER_DIR		= includes

ASM_DIR			= assembler
COREWAR_DIR		= vm
LIB_DIR			= libft
ASM_SRCS		= $(addprefix $(ASM_DIR)/, $(_ASM_SRCS))
COREWAR_SRCS	= $(addprefix $(COREWAR_DIR)/, $(_COREWAR_SRCS))
LIBFT			= $(addprefix $(LIB_DIR)/, $(_LIBFT))
ASM_OBJS		= $(ASM_SRCS:.c=.o)
COREWAR_OBJS	= $(COREWAR_SRCS:.c=.o)

#COLORS
_CYAN=\x1b[36m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_END=\x1b[0m

all:  lib $(ASM) $(NAME)

$(ASM): $(LIBFT) $(ASM_OBJS)
			@$(CC) $(CFLAGS) -o $(ASM) $(ASM_OBJS) -L$(LIB_DIR) -lft -I $(HEADER_DIR)
			@echo "$(ASM) : $(_GREEN)Done$(_END)"

$(NAME): $(LIBFT) $(COREWAR_OBJS)
			@$(CC) $(CFLAGS) -o $(NAME) $(COREWAR_OBJS) -L$(LIB_DIR) -lft -lncurses -I $(HEADER_DIR)
			@echo "$(NAME) : $(_GREEN)Done$(_END)"

lib:
			@make -C $(LIB_DIR)

%.o : %.c
			@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_DIR)

clean:
			@make fclean -C $(LIB_DIR)
			@/bin/rm -f $(ASM_OBJS)
			@/bin/rm -f $(COREWAR_OBJS)
			@echo "$(ASM) clean : $(_GREEN)Done$(_END)"
			@echo "$(NAME) clean : $(_GREEN)Done$(_END)"
	
fclean: clean
			@/bin/rm -f $(ASM)
			@/bin/rm -f $(NAME)
			@echo "$(ASM) fclean : $(_GREEN)Done$(_END)"
			@echo "$(NAME) fclean : $(_GREEN)Done$(_END)"

re:
			@make fclean
			@make

.PHONY: all clean fclean re
