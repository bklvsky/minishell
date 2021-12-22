# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/27 21:46:39 by dselmy            #+#    #+#              #
#    Updated: 2021/12/23 01:05:35 by dselmy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

INC_DIR = ./includes/
LIBFT_DIR = ./libft/

SRCS =	$(wildcard *.c)
OBJ = $(SRCS:.c=.o)
DEP = $(SRCS:.c=.d)

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
		@make -C $(LIBFT_DIR)
		gcc -o $(NAME) $(CFLAGS) -I$(INC_DIR) $(OBJ) $(LIBFT_DIR)libft.a

%.o:	%.c
		gcc -c $(CFLAGS) -I$(INC_DIR) $< -o $@ -MD

clean:
		@make clean -C $(LIBFT_DIR)
		rm -f $(OBJ) $(DEP)

fclean: clean
		@make fclean -C $(LIBFT_DIR)
		rm -f $(NAME)
		
re: fclean all

include $(wildcard $(DEP))

.PHONY: all clean fclean re
