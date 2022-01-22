# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/27 21:46:39 by dselmy            #+#    #+#              #
#    Updated: 2022/01/22 17:14:38 by dselmy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parser

INC_DIR = ./includes/
LIBFT_DIR = ./libft/

SRCS =	$(wildcard *.c) $(wildcard ./buildins/*.c)
BUILDINS = $(wildcard ./buildins/*.c)
OBJ = $(SRCS:.c=.o)
#OBJBUILDINS = $(BUILDINS:.c=.o)
DEP = $(SRCS:.c=.d) 

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
		@make -C $(LIBFT_DIR)
		gcc -o $(NAME) $(CFLAGS) -I./buildins/ -I$(INC_DIR) $(OBJ) $(LIBFT_DIR)libft.a -L/Users/dselmy/.brew/Cellar/readline/8.1.1/lib -lreadline

%.o:	%.c
		gcc -c $(CFLAGS) -I./buildins/ -I$(INC_DIR) $< -o $@ -MD

clean:
		@make clean -C $(LIBFT_DIR)
		rm -f $(OBJ) $(DEP)

fclean: clean
		@make fclean -C $(LIBFT_DIR)
		rm -f $(NAME)
		
re: fclean all

include $(wildcard $(DEP))

.PHONY: all clean fclean re
