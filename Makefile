# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/16 21:15:36 by fbabin            #+#    #+#              #
#    Updated: 2018/02/01 14:00:09 by fbabin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN			= lem-in
LEM_INV			= lem-in-visu

CC				= gcc -g3
CFLAGS			= -Wall -Werror -Wextra

_SRCS			=	get_rooms.c get_rooms2.c get_rooms3.c \
					get_pipes.c get_pipes2.c get_pipes3.c \
					launchers.c freeer.c \
					ft_displays.c atoi_check.c solver.c roads.c \
					affichage.c affichage_cycle.c affichage_move.c \
					affichage_first_ants.c affichage2.c lem_in2.c \
					solver2.c solver3.c freeer2.c roads2.c

_L_SRCS			=	lem_in.c
_L_SRCS			+=	$(_SRCS)
_V_SRCS			=	lem_in_visu.c get_room_states.c visu_utils.c \
					generate_map.c deal_key.c bresenham.c draw.c \

_V_SRCS			+=	$(_SRCS)

_MLX			=	libmlx.a
_LIBFT			=	libft.a
HEADER_DIR		=	includes
HEADER			=	$(HEADER_DIR)/lem_in.h

SRCS_DIR		= srcs
LIB_DIR			= libft
MLX_DIR			= minilibx_macos
L_SRCS			= $(addprefix $(SRCS_DIR)/, $(_L_SRCS))
V_SRCS			= $(addprefix $(SRCS_DIR)/, $(_V_SRCS))
MLX				= $(addprefix $(MLX_DIR)/, $(_MLX))
LIBFT			= $(addprefix $(LIB_DIR)/, $(_LIBFT))
L_OBJS			= $(L_SRCS:.c=.o)
V_OBJS			= $(V_SRCS:.c=.o)

#COLORS
_CYAN=\x1b[36m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_END=\x1b[0m

all: $(LEM_IN) $(LEM_INV)

$(LEM_IN): $(HEADER) $(LIBFT) $(L_OBJS)
		@$(CC) $(CFLAGS) -o $(LEM_IN) $(L_OBJS) -L$(LIB_DIR) -lft -I $(HEADER_DIR)
		@echo "$(LEM_IN) : $(_GREEN)Done$(_END)"

$(LEM_INV): $(HEADER) $(LIBFT) $(MLX) $(V_OBJS)
		@$(CC) $(CFLAGS) -o $(LEM_INV) $(V_OBJS) -I /usr/local/include -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit -L$(LIB_DIR) -lft -I $(HEADER_DIR)
		@echo "$(LEM_INV) : $(_GREEN)Done$(_END)"

$(MLX):
		@make -C $(MLX_DIR)

$(LIBFT):
		@make -C $(LIB_DIR)

%.o : %.c
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_DIR)

clean:
		@make fclean -C $(LIB_DIR)
		@make clean -C $(MLX_DIR)
		@/bin/rm -f $(L_OBJS) $(V_OBJS)
		@echo "$(LEM_IN) clean : $(_GREEN)Done$(_END)"
		@echo "$(LEM_INV) clean : $(_GREEN)Done$(_END)"

fclean: clean
		@/bin/rm -f $(LEM_IN) $(LEM_INV)
		@echo "$(LEM_IN) fclean : $(_GREEN)Done$(_END)"
		@echo "$(LEM_INV) fclean : $(_GREEN)Done$(_END)"

re:
		@make fclean
		@make

.PHONY: all clean fclean re
