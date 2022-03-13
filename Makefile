NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRCS_DIR = $(shell find srcs -type d)
OBJS_DIR = objs
INC_DIR = ./ducklinclude/
LIBFT_DIR = ./libft_duck

LIBS = -L$(LIBFT_DIR) -lft -lreadline
INCLUDES = -I$(LIBFT_DIR)/Includes -I$(INC_DIR)

vpath %.c $(foreach dir, $(SRCS_DIR), $(dir):)

SRCS = cd.c echo.c env.c exit.c export.c pwd.c unset.c \
	error_manager.c error_utils.c sig_handler.c \
	command_manager.c link_fd_redir.c \
	expand_join.c expand_manager.c expand_split_seps.c \
	expand_split_whitespace.c expand_tokenize.c \
	expand_utils.c expand_var_utils.c expand_var.c \
	split_quotes_dollar.c \
	split_manager.c split_separators.c split_whitespaces.c \
	tokenize.c \
	del_struct.c init_struct.c struct_utils.c \
	cmd_manager.c create_cl.c redir_error.c \
	exec_errors.c exec_utils.c execution.c \
	ft_builtins.c ft_here_doc.c ft_redir.c ft_utils_tmp.c \
	main.c \
	print_tokens_cmds.c

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

all: $(LIBFT_DIR)/libft.a $(NAME)

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR) all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(LIBS)

$(OBJS_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
		rm -rf $(OBJS_DIR)

fclean: clean
		rm -rf $(NAME)

cleanall: fclean
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY : all clean fclean re
