/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_quack_shell.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:52:38 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/21 15:46:17 by vduriez          ###   ########.fr       */
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
# include "libft.h"

# define ERNO_QUOTE 0
# define ERNO_PIPE 1

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

extern int	g_exit_status;

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
	struct s_env_var	*next;
}				t_env_var;

typedef struct s_env
{
	t_env_var	*first;
}				t_env;

//			Init Structs
t_token		*ft_create_empty_token(void);
t_cmd		*ft_create_cmd(void);

//?			Parsing
//			Split
void		split_manager(char *line, t_env *env);
void		split_whitespaces(char *str, char *(**args));
void		split_seps(char *(**args));
void		separate_separator(char *(**args), char *sep, int i_args);
//
//			Tokenize
void		tokenize_manager(char *(**args), t_env *env);
int			get_arg_type(char *arg, int prev_type);
//
//			Expand
void		expand_caller(t_token *tokens, t_env *env);
void		expand_manager(t_token **it, t_env *env);

char		**expand_split_manager(char *str);
char		**split_expand_prefix(char *str, int *i);
void		split_quotes_expand(char *(**arr), char *str, int *index);
void		split_dollar_expand(char *(**arr), char *str, int *index);
void		expand_split_whitespaces(char *(**arr));

void		expand_var(char *(*str), t_env *env);

void		join_vars(char *(**arr));

void		tokenize_expanded_vars(char **arr, t_token **parent);

void		convert_spaces(char *(**arr), char space);
void		del_quotes(char *(*str));
//
//			Commands
void		command_manager(t_token *tokens, t_env *env);
void		link_fd_redir(t_token **tokens);
//

//?			Builtins
int			is_builtin(char *cmd);
void		ft_builtins(char **cmd, t_env *env, int is_piped);
//* PWD
void		ft_pwd(void);
//* CD
void		ft_cd(char **cmd, t_env *env);
void		env_change_and_error_management(t_env *env, char **cmd, int i);
void		invalid_path(char **cmd);
//* ECHO
void		ft_echo(char **s);
//* EXPORT
void		ft_export(t_env *env, char **cmd);
void		replace_var(t_env *env, char *name, char *value);
int			existing_name(t_env *env, char *name);
int			format_export_ok(char *var);
void		add_env_var(t_env *env, char **var);
//* UNSET
int			format_unset_ok(char *var, int *err);
void		ft_unset(t_env *env, char **name);
//* ENV
void		get_env(char **envp, t_env *env);
void		ft_env(t_env *env);
char		*get_in_env(t_env *env, char *name);
int			env_size(t_env *env);
char		**env_cl_to_arr(t_env *env);
char		*get_env_name(t_env *env, char *name);
//* EXIT
void		ft_exit(char **err, t_env *env, int is_piped);
void		ft_clear(t_env *env);
void		clear_and_exit(char **err, t_env *env);
int			is_num(char *s);
//?			Builtins

//* REDIR
void		apply_redir(char *str, int type, t_cmd *cmd, int *err);
void		redirection(t_cmd *cmd, int fd[4]);
int			invalid_filename(char *filename, int *err, char *FILENO);

//* EXEC
void		execution(t_cmd *cmd, t_env *env, int fd[4], int is_piped);
void		ft_exec(char **cmd, char **envp);
char		**get_cmd_str(t_cmd *cmd);
void		cmd_not_found(char *cmd, char **tmp_paths);
int			is_builtin(char *cmd);

//* CMDS_MANAGER
void		cmd_manager(t_env *env, t_cmd *cmd);
void		close_wait_clear(t_cmd_lst *cmds, int fd[4], t_env *env);
void		init_fds(int fd[4]);
void		closepipe(int fd[3]);
void		close_all_fds(int fd[4], t_cmd *cmd);
void		clear_token_cl(t_token *lst);
void		rm_here_doc_tmp_file(t_env *env);
void		rm_cmds(t_cmd_lst *cmd);
void		get_here_doc(char *limiter);

//			CL
t_env_var	*ft_create_elem(char *name, char *value);
void		ft_addfirst(t_env *env, char *name, char *value);
void		ft_addlast(t_env *env, char *name, char *value);
void		ft_rmvar(t_env *env, char *var_name);
//			CL

//			ERRORS
void		error_manager(int erno);
//

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