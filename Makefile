# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/29 15:44:46 by vduriez           #+#    #+#              #
#    Updated: 2022/02/07 17:11:38 by vduriez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = minishell

NAME_FSAN = minishell_fsanitize

INCLUDES = ducklinclude/mini-quack-shell.h

FSANITIZE = -fsanitize=address -fsanitize=address -g3

SRCS =	srcs/main.c					\
		srcs/builtins/pwd.c			\
		srcs/builtins/echo.c		\
		srcs/builtins/env.c			\
		srcs/builtins/cd.c			\
		srcs/builtins/exit.c		\
		srcs/builtins/export.c		\
		srcs/builtins/unset.c		\
		srcs/ft_builtins.c			\
		srcs/create_cl.c			\
		srcs/execution.c			\
		srcs/ft_utils_tmp.c

OBJ = $(SRCS:.c=.o)

OBJ_BONUS = $(SRCS_BONUS:.c=.o)

all:		$(NAME)

$(NAME):	$(INCLUDES) $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lreadline

fsan:	$(NAME_FSAN)

$(NAME_FSAN):	$(INCLUDES) $(OBJ)
		$(CC) $(FLAGS) $(FSANITIZE) $(OBJ) -o $(NAME_FSAN) -lreadline
clean:
		rm -rf $(OBJ)

sanclean:
		rm -rf $(NAME_FSAN)

fclean: clean
		rm -rf $(NAME) $(NAME_FSAN)

re: fclean all

.PHONY : all clean fclean re bonus
