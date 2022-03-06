/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_quack_shell.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 07:22:11 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/06 03:43:00 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_QUACK_SHELL_H
# define MINI_QUACK_SHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>
# include "libft.h"
# include "ft_get_file.h"

# define ERNO_SYNTAX 0
# define ERNO_ACCESS 1
# define ERNO_NOCMD 2
# define ERNO_ISDIR 3
# define ERNO_ARGS 4
# define ERNO_PATH 5
# define ERNO_CD 6
# define ERNO_UNSET 7
# define ERNO_EXPORT 8
# define ERNO_NOFILEDIR 9
# define ERNO_EX_NUM 10
# define ERNO_NOEXEC 11

# define NO_TYPE -1
# define WORD 0
# define PIPE 1
# define FD 2
# define LIMITER 3
# define RIN 4
# define ROUT 5
# define DROUT 6
# define HERE_DOC 7
# define HERE_DOC_NAME ".tmprry_mini_QUACK_shell_ull_never_guess_its_name"
# define HERE_DOC_PATH "objs/.tmprry_mini_QUACK_shell_ull_never_guess_its_name"

typedef struct s_status
{
	int	exit_status;
	int	pid;
	int	hd_fd;
}				t_status;

extern t_status	g_status;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_cmd
{
	t_token			*arg;
	t_token			*redir;
	int				fdin;
	int				fdout;
	int				pid;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;

typedef struct s_cmd_list
{
	struct s_cmd	*first;
}				t_cmd_lst;

typedef struct s_env_var
{
	char				*name;
	char				*value;
	int					to_print;
	struct s_env_var	*next;
}				t_env_var;

typedef struct s_env
{
	t_env_var	*first;
}				t_env;

//			Structs
t_token		*ft_create_empty_token(void);
t_token		*get_last_token(t_token *tokens);
t_cmd		*ft_create_cmd(void);
void		free_token(t_token *tokens);
void		free_one_token(t_token *token);
void		free_cmds(t_cmd *cmds);

//			Main
char		*get_prompt_prefix(t_env *env);
//
//?			Parsing
//			Split
void		split_manager(char *line, t_env *env);
int			syntax_errors(char **args);
void		misc_error(char *str, char pb, int *index);
int			pipe_error(char *str);

void		split_seps(char *(**args));
void		check_separator(char *(**args), int i_args);
void		separate_separator(char *(**args), char *sep, int i_args);
char		*del_sep(char *src, int index);

void		split_whitespaces(char *str, char *(**args));
int			split_skip_quotes(char *(**args), char *str, int *index,
				char **tmp);
int			ret_error_quotes(char *str, int i, char *tmp, char *(**args),
				char quote);
//
//			Tokenize
void		tokenize_manager(char *(**args), t_env *env);
int			get_arg_type(char *arg, int prev_type);
int			check_tokens_type(t_token *tokens);
//
//			Expand
void		expand_caller(t_token *tokens, t_env *env);
void		expand_manager(t_token **it, t_env *env);

char		**expand_split_manager(char *str);
char		**split_expand_prefix(char *str, int *i);
void		add_splited_to_args(char *(**args), char *str);

void		split_quotes_expand(char *(**arr), char *str, int *index);
void		split_dollar_expand(char *(**arr), char *str, int *i);

void		expand_split_whitespaces(char *(**arr));
void		add_non_whitespace(char *(**arr), char *cpy);
void		expand_skip_quotes(char *(**arr), char **cpy, int *index);

void		expand_vars_manager(t_token *it, char *(**arr), t_env *env);
void		expand_var(char **str, t_env *env, int hd);
void		get_str(char *value, char **str);

int			check_quote_expand(char **str);
int			expand_exeptions(char **str, int i, char *cpy, char *value);
char		*get_exp_var_name(char *str, int *index);
void		join_pre_sufix_expanded_var(char **str, int i, char **value,
				char *cpy);

void		join_vars(char *(**arr));

void		tokenize_expanded_vars(char **arr, t_token **parent);
void		relink_parent_to_himself(t_token **parent);
void		no_link_parent(t_token **parent);
t_token		*make_new_tokens(char **arr);

void		convert_spaces(char *(**arr), char space);
void		del_quotes(char *(*str));
void		copy_str_without_quotes(char *(*str), int *i, char quote);
//
//			Commands
void		command_manager(t_token *tokens, t_env *env);
void		free_pipe_make_cmd(t_cmd **it_c, t_token **it_t);
void		assign_token_cmd(t_cmd **it_c, t_token **it_t, int assign);
void		unlink_cmd_token(t_token *cmd_t, t_token **it_t);

void		link_fd_redir(t_token **tokens);
void		relink_node_parent(t_token **it, t_token **head);

//

//?			Builtins
int			is_builtin(char *cmd);
void		ft_builtins(char **cmd, t_env *env, int fd[6], t_cmd_lst *cmds);
//* PWD
void		ft_pwd(void);
//* CD
void		ft_cd(char **cmd, t_env *env);
void		env_change_and_error_management(t_env *env, char **cmd, int i);
//* ECHO
void		ft_echo(char **s);
//* EXPORT
void		ft_export(t_env *env, char **cmd);
void		export_var(int i[2], char **cmd, t_env *env);
void		replace_var(t_env *env, char *name, char *value);
int			existing_name(t_env *env, char *name);
int			format_export_ok(char *var);
void		add_env_var(t_env *env, char **var, int to_print);
//* UNSET
int			format_unset_ok(char *var);
void		ft_unset(t_env *env, char **name);
//* ENV
void		get_env(char **envp, t_env *env);
void		ft_env(t_env *env);
int			env_size(t_env *env);
char		**env_cl_to_arr(t_env *env);
char		*get_env_name(t_env *env, char *name);
//* EXIT
void		ft_exit(char **err, t_env *env, int is_piped, t_cmd_lst *cmds);
void		ft_clear(t_env *env);
void		clear_and_exit(char **err, t_env *env, t_cmd_lst *cmds);
int			is_num(char *s);
//?			Builtins

//* REDIR
void		apply_redir(t_token *tmp, t_cmd *cmd, int *i);
void		redir_pipe(t_cmd *cmd, int fd[6]);
void		redir_out(t_cmd *cmd, char *str, int type, int *i);
void		abort_exec(char **cmd, t_cmd_lst *cmds, t_env *env, int fd[6]);
void		redirection(t_cmd *cmd, int fd[6]);
void		get_over_here_docs(t_cmd_lst *cmds, t_env *env, int *sig);
int			invalid_filename(char *filename, char *FILENO, int *i);

//* EXEC
void		execution(t_cmd *cmd, t_env *env, int fd[6], t_cmd_lst *cmds);
void		apply_exec(char **str_cmd, int fd[6], t_env *env, t_cmd_lst *cmds);
void		ft_exec(char **cmd, char **envp, t_cmd_lst *cmds);
void		no_cmd(char **cmd, char **envp, t_cmd_lst *cmds);
char		**get_cmd_str(t_cmd *cmd);
char		*get_path(char *path, char *cmd);
void		failed_fork(t_cmd *cmd, char **str_cmd);
void		cmd_not_found(char **cmd, char **tmp_paths, char **env,
				t_cmd_lst *cmds);
int			is_builtin(char *cmd);

//* CMDS_MANAGER
void		cmd_manager(t_env *env, t_cmd *cmd);
void		close_wait_clear(t_cmd_lst *cmds, int fd[6], t_env *env);
void		init_fds(int fd[6]);
void		closepipe(int fd[4]);
void		close_all_fds(int fd[6], t_cmd *cmd);
void		clear_token_cl(t_token *lst);
void		rm_here_doc_tmp_file(t_env *env, t_cmd_lst *cmds);
void		rm_cmds(t_cmd_lst *cmd);
char		*get_here_doc(char *limiter, t_env *env, int *sig);

//			CL
t_env_var	*ft_create_elem(char *name, char *value, int to_print);
void		ft_addlast(t_env *env, char *name, char *value, int to_print);
void		ft_rmvar(t_env *env, char *var_name);
//			CL

void		ft_clear(t_env *env);
void		ft_free(char **s);
int			is_num(char *s);

//?			SIGNAL HANDLER
void		sig_handler(int signum);
void		handler_parent(int signum);
void		handler_child(int signum);
//?

//?			ERRORS
void		error_manager(int erno, char *str);
char		*get_cmd_error(int erno, char *cmd);
char		*get_complex_error(int erno, char *cmd);
char		*get_syntax_error(char *str);
void		get_error_redir(t_token *next);
//?

//!				DEBUG
void		print_tokens(t_token *tokens);
void		print_cmds(t_cmd *cmds);
//!

//!				TO REMOVE WHEN LIBFT IMPLANTED
// int			ft_strlen(char *s);
// int			ft_strncmp(const char *s1, const char *s2, size_t n);
// char		*ft_strdup(const char *s1);
char		*ft_strndup(const char *s1, int n);
// char		**ft_split(char const *str, char c);
// char		*ft_strjoin(char *s1, char *s2);
// int			ft_atoi(const char *str);
// int			ft_strcmp(const char *s1, const char *s2);
//!				TO REMOVE WHEN LIBFT IMPLANTED

#endif