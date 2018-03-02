# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/27 17:05:52 by fbabin            #+#    #+#              #
#    Updated: 2018/03/02 13:56:35 by pnardozi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR			= corewar

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -g3

_SRCS			=	main.c op.c visu.c displays.c parse_champs.c load_champs.c \
					init_arena.c init_players.c init_player2.c check_number.c \
					check_dump.c \
					init_process.c run_cycle.c handle_process.c \
					freeall.c hex_to_dec.c modif_pc.c check_param_type.c \
					check_get_registry.c get.c set.c live.c ld.c lld.c \
					ldi.c st.c sti.c add.c sub.c bitwise.c zjmp.c fork.c \
					long_fork.c aff.c visu2.c visu3.c visu4.c\

_LIBFT			=	libft.a
HEADER_DIR		=	includes
HEADER			=	$(HEADER_DIR)/vm.h

SRCS_DIR		=	srcs
LIB_DIR			=	../libft
SRCS			=	$(addprefix $(SRCS_DIR)/, $(_SRCS))
LIBFT			=	$(addprefix $(LIB_DIR)/, $(_LIBFT))
OBJS			=	$(SRCS:.c=.o)

#COLORS
_CYAN=\x1b[36m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_END=\x1b[0m

all: $(COREWAR)

$(COREWAR): $(HEADER) $(LIBFT) $(OBJS)
		@$(CC) $(CFLAGS) -o $(COREWAR) $(OBJS) -L$(LIB_DIR) -lft -lncurses -I $(HEADER_DIR) -I ../includes
		@echo "$(COREWAR) : $(_GREEN)Done$(_END)"

$(LIBFT):
		@make -C $(LIB_DIR)

%.o : %.c
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_DIR)

clean:
		@make fclean -C $(LIB_DIR)
		@/bin/rm -f $(OBJS)
		@echo "$(COREWAR) clean : $(_GREEN)Done$(_END)"

fclean: clean
		@/bin/rm -f $(COREWAR)
		@echo "$(COREWAR) fclean : $(_GREEN)Done$(_END)"

re:
		@make fclean
		@make

.PHONY: all clean fclean re
