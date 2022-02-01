# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/29 15:44:46 by vduriez           #+#    #+#              #
#    Updated: 2022/02/01 17:23:37 by vduriez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = minishell

INCLUDES = ducklinclude/mini-quack-shell.h

FSANITIZE = -fsanitize=address -fsanitize=undefined -g3

SRCS =	srcs/main.c					\
		srcs/builtins/pwd.c			\
		srcs/builtins/echo.c		\
		srcs/builtins/env.c			\
		srcs/builtins/cd.c			\
		srcs/builtins/exit.c		\
		srcs/create_cl.c			\
		srcs/execution.c			\
		srcs/ft_utils_tmp.c

OBJ = $(SRCS:.c=.o)

OBJ_BONUS = $(SRCS_BONUS:.c=.o)

all:		$(NAME)

$(NAME):	$(INCLUDES) $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lreadline

fsanitize:	$(FSANITIZE)

$(FSANITIZE):	$(INCLUDES) $(OBJ)
		$(CC) $(FLAGS) $(FSANITIZE) $(OBJ) -o $(NAME) -lreadline
clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re bonus
