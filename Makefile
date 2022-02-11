NAME = minishell
ALBE = a_minishell
VINC = v_minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

DEBUG =
ifdef DEBUG
CFLAGS += -fsanitize=address -fsanitize=address -g3
endif

SRCS_DIR = $(shell find srcs -type d)
OBJS_DIR = objs
INC_DIR = ./ducklinclude/
LIBFT_DIR = ./libft_duck

LIBS = -L$(LIBFT_DIR) -lft -lreadline
INCLUDES = -I$(LIBFT_DIR)/Includes -I$(INC_DIR)

vpath %.c $(foreach dir, $(SRCS_DIR), $(dir):)

SRCS = srcs/main_Xec.c \
		srcs/builtins/pwd.c \
		srcs/builtins/echo.c \
		srcs/builtins/env.c \
		srcs/builtins/cd.c \
		srcs/builtins/exit.c \
		srcs/builtins/export.c \
		srcs/builtins/unset.c \
		srcs/ft_builtins.c \
		srcs/create_cl.c \
		srcs/execution.c \
		srcs/ft_utils_tmp.c

A_SRCS = albe_main.c \
		split_manager.c \
		split_whitespaces.c split_separators.c \
		tokenize.c init_struct.c \
		print_tokens.c \
		expand_manager.c split_quotes_dollar.c \
		export.c \
		ft_utils_tmp.c

V_SRCS = main_Xec.c \
		builtins/pwd.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/cd.c \
		builtins/exit.c \
		builtins/export.c \
		builtins/unset.c \
		ft_builtins.c \
		create_cl.c \
		execution.c \
		ft_utils_tmp.c


OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
A_OBJS = $(addprefix $(OBJS_DIR)/,$(A_SRCS:.c=.o))
V_OBJS = $(addprefix $(OBJS_DIR)/,$(V_SRCS:.c=.o))

all: $(LIBFT_DIR)/libft.a $(NAME)

albe:$(LIBFT_DIR)/libft.a $(ALBE)

vinc:$(LIBFT_DIR)/libft.a $(VINC)

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR) all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(LIBS)

$(ALBE): $(A_OBJS)
	$(CC) $(CFLAGS) $^ -o $(ALBE) $(LIBS)

$(VINC): $(V_OBJS)
	$(CC) $(CFLAGS) $^ -o $(VINC) $(LIBS)

$(OBJS_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
		rm -rf $(OBJS)
		rm -rf $(A_OBJS)
		rm -rf $(V_OBJS)

fclean: clean
		rm -rf $(NAME)
		rm -rf $(ALBE)
		rm -rf $(VINC)

cleanall: fclean
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY : all clean fclean re
