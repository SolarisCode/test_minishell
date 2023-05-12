# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 00:02:38 by melkholy          #+#    #+#              #
#    Updated: 2023/05/12 14:48:24 by estruckm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = main.c \
			parsing_utils.c \
			parsing_redirection.c \
			lexer.c \
			parser.c \
			input_analysis.c \
			signals.c \
			execution.c \
			link_list_utils/create_list.c \
			link_list_utils/link_list.c \
			builtins/echo.c \
			builtins/execute_buildins.c \
			builtins/env.c \
			builtins/pwd.c \
			builtins/cd.c \
			builtins/export.c \
			builtin_utils/builtins_utils.c \
			builtins/builtins.c \

NAME = minishell
LIBFT = ./Libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I $(HOME)/goinfre/.brew/opt/readline/include/

all: $(NAME)

$(NAME): $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT) -L$(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline $(SOURCES) -o $(NAME)

$(LIBFT):
	make -C Libft

clean:
	make -C Libft clean

fclean: clean
	make fclean -C Libft
	rm -rf $(NAME) minishell.dSYM

re: fclean all

.PHONY: all bonus libft clean fclean re
