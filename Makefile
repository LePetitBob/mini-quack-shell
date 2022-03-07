NAME = minishell

CC = clang
# CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

SRCS_DIR = $(shell find srcs -type d)
OBJS_DIR = objs
INC_DIR = ./ducklinclude/
LIBFT_DIR = ./libft_duck

LIBS = -L$(LIBFT_DIR) -lft -lreadline
INCLUDES = -I$(LIBFT_DIR)/Includes -I$(INC_DIR)

vpath %.c $(foreach dir, $(SRCS_DIR), $(dir):)

SRCS = builtins/pwd.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/cd.c \
		builtins/exit.c \
		builtins/export.c \
		builtins/unset.c \
		ft_builtins.c \
		ft_redir.c \
		create_cl.c \
		execution.c \
		ft_here_doc.c \
		cmd_manager.c \
		ft_utils_tmp.c \
		main.c \
		split_manager.c \
		split_whitespaces.c \
		split_separators.c \
		tokenize.c \
		expand_manager.c \
		split_quotes_dollar.c \
		expand_split_seps.c \
		expand_split_whitespace.c \
		expand_var.c expand_var_utils.c \
		expand_join.c \
		expand_tokenize.c \
		expand_utils.c \
		del_struct.c \
		command_manager.c link_fd_redir.c \
		error_manager.c error_utils.c sig_handler.c \
		init_struct.c del_struct.c struct_utils.c \
		redir_error.c \
		exec_errors.c \
		exec_utils.c \
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
