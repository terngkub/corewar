# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/16 21:15:36 by fbabin            #+#    #+#              #
#    Updated: 2018/02/09 18:20:46 by nkamolba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM				= asm

CC				= gcc -g3
CFLAGS			= -Wall -Werror -Wextra

_ASM_SRCS		=	asm.c check_name_comments.c check_instruction_line.c check_parameters.c get_param_type.c ft_trim.c ft_remove_space.c ft_error.c print_inst_list.c print_labels_list.c \
					op.c \

_LIBFT			=	libft.a
HEADER_DIR		=	includes
HEADER			=	$(HEADER_DIR)/asm.h

SRCS_DIR		= srcs
ASM_DIR			= assembler
LIB_DIR			= libft
ASM_SRCS		= $(addprefix $(ASM_DIR)/, $(_ASM_SRCS))
LIBFT			= $(addprefix $(LIB_DIR)/, $(_LIBFT))
ASM_OBJS		= $(ASM_SRCS:.c=.o)

#COLORS
_CYAN=\x1b[36m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_END=\x1b[0m

all: $(ASM)

$(ASM): $(HEADER) $(LIBFT) $(ASM_OBJS)
		@$(CC) $(CFLAGS) -o $(ASM) $(ASM_OBJS) -L$(LIB_DIR) -lft -I $(HEADER_DIR)
		@echo "$(ASM) : $(_GREEN)Done$(_END)"

$(LIBFT):
		@make -C $(LIB_DIR)

%.o : %.c
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_DIR)

clean:
		@make fclean -C $(LIB_DIR)
		@/bin/rm -f $(ASM_OBJS)
		@echo "$(ASM) clean : $(_GREEN)Done$(_END)"

fclean: clean
		@/bin/rm -f $(ASM)
		@echo "$(ASM) fclean : $(_GREEN)Done$(_END)"

re:
		@make fclean
		@make

.PHONY: all clean fclean re
