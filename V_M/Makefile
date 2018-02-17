# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnardozi <pnardozi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/19 14:34:26 by pnardozi          #+#    #+#              #
#    Updated: 2018/02/17 18:33:27 by nkamolba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3

COREWAR = corewar

LIBFT_INCLUDES_PATH = ../libft/includes/
PRINTF_INCLUDES_PATH = ./libft/includes/

COREWAR_SRCS_PATH = ./srcs/
COREWAR_INCLUDES_PATH = ./includes/
COREWAR_OBJ_PATH = ./obj/

COREWAR_SRCS_NAME = main.c \
					op.c \
					displays.c \
					parse_champs.c \
					load_champs.c \
					init_arena.c \
					init_players.c \
					init_process.c \
					run_cycle.c \
					hex_to_dec.c \
					find_player.c \
					check_param_type.c \
					get.c \
					set.c \
					live.c \
					load.c \
					store.c \
					fork.c \
					long_fork.c \
					aff.c \

COREWAR_OBJ_NAME =$(COREWAR_SRCS_NAME:.c=.o)

LIBFT_INC = $(addprefix -I,$(LIBFT_INCLUDES_PATH))
PRINTF_INC = $(addprefix -I,$(PRINTF_INCLUDES_PATH))

COREWAR_SRCS = $(addprefix $(COREWAR_SRCS_PATH),$(COREWAR_SRCS_NAME))
COREWAR_OBJ = $(addprefix $(COREWAR_OBJ_PATH),$(COREWAR_OBJ_NAME))
COREWAR_INC = $(addprefix -I,$(COREWAR_INCLUDES_PATH))

LIB_PATH = ../libft/
LIB_NAME = libft.a
LIB = $(addprefix $(LIB_PATH),$(LIB_NAME))

RED = \033[31m
GREEN = \033[32m
END = \033[0m

all: $(LIB_NAME) $(COREWAR)

$(LIB_NAME):
	make -C $(LIB_PATH)

$(COREWAR): $(COREWAR_OBJ)
	$(CC) $(CFLAGS) -o $(COREWAR) $(COREWAR_OBJ) $(LIB)
	@echo "$(GREEN)COREWAR READY$(END)"

$(COREWAR_OBJ_PATH)%.o: $(COREWAR_SRCS_PATH)%.c
	@mkdir -p $(COREWAR_OBJ_PATH)
	$(CC) -c $(CFLAGS) $(COREWAR_INC) $(LIBFT_INC) $(PRINTF_INC) -o $@ -c $<

clean:
	make clean -C $(LIB_PATH)
	/bin/rm -rf $(COREWAR_OBJ_PATH)
	@echo "$(RED)COREWAR OBJECTS REMOVE$(END)"

fclean: clean
	make fclean -C $(LIB_PATH)
	/bin/rm -rf $(COREWAR)
	@echo "$(RED)COREWAR REMOVE$(END)"

re: 
	make fclean
	make

.PHONY: all clean fclean re
