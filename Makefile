# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/27 21:46:39 by dselmy            #+#    #+#              #
#    Updated: 2022/06/30 18:07:36 by dselmy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC_DIR = ./includes/
BUILDINS_DIR = ./buildins/
LIBFT_DIR = ./libft/

SRCS =	engine.c \
		exec.c \
		expand_env_var.c \
		init_struct.c \
		main.c \
		manage_redirect.c \
		parse_token.c \
		parser.c \
		redirect_fds.c \
		shutdown.c \
		signals.c \
		utils_exec.c \
		utils_new_token.c \
		utils_open_files.c \
		utils_parse_token.c \
		utils_parser.c \
		utils_parser_checks.c \
		utils_shutdown_close.c \
		utils_shutdown_free.c \
		utils_shutdown_message.c \
		$(BUILDINS_DIR)cd.c \
		$(BUILDINS_DIR)echo.c \
		$(BUILDINS_DIR)env.c \
		$(BUILDINS_DIR)env_proc.c \
		$(BUILDINS_DIR)env_proc_utils.c \
		$(BUILDINS_DIR)exit.c \
		$(BUILDINS_DIR)exit_utils.c \
		$(BUILDINS_DIR)export.c \
		$(BUILDINS_DIR)export_utils.c \
		$(BUILDINS_DIR)pwd.c \
		$(BUILDINS_DIR)unset.c
OBJ = $(SRCS:.c=.o)
DEP = $(SRCS:.c=.d) 

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
		@make -C $(LIBFT_DIR)
		gcc -o $(NAME) $(CFLAGS) -I$(BUILDINS_DIR) -I$(INC_DIR) $(OBJ) \
		$(LIBFT_DIR)libft.a -lreadline

%.o:	%.c
		gcc -c $(CFLAGS) -I$(BUILDINS_DIR) -I$(INC_DIR) $< -o $@ -MD

clean:
		@make clean -C $(LIBFT_DIR)
		rm -f $(OBJ) $(DEP)

fclean: clean
		@make fclean -C $(LIBFT_DIR)
		rm -f $(NAME)
		
re: fclean all

include $(wildcard $(DEP))

.PHONY: all clean fclean re
