/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_quack_shell.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:52:38 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/10 18:46:10 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_QUACK_SHELL
# define MINI_QUACK_SHELL
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

# define WORD 0
# define PIPE 1
# define FD 2
# define LIMITER 3
# define RIN 4
# define ROUT 5
# define DROUT 6
# define HERE_DOC 7

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

//?			Builtins
int		is_builtin(char *cmd);
void	ft_builtins(char **cmd, t_env *env);
void	ft_pwd(void);
void	ft_cd(char **cmd, t_env *env);
void	ft_echo(char **s);
void	ft_env(t_env *env);
void	get_env(char **envp, t_env *env);
char	**env_cl_to_arr(t_env *env);
void	ft_exit(char **err, t_env *env);
void	ft_export(t_env *env, char **cmd);
void	replace_var(t_env *env, char *name, char *value);
void	ft_unset(t_env *env, char **name);
int		existing_name(t_env *env, char *name);
int		format_ok(char *var);
//?			Builtins

//			CL
t_env_var	*ft_create_elem(char *name, char *value);
void		ft_addfirst(t_env *env, char *name, char *value);
void		ft_addlast(t_env *env, char *name, char *value);
void		ft_rmvar(t_env *env, char *var_name);
//			CL

void	redir(t_cmd *cmd);
char	**env_cl_to_arr(t_env *env);
void	execution(t_cmd *cmd, t_env *env);
void	ft_exec(char **cmd, char **envp);
void	ft_clear(t_env *env);
void	ft_free(char **s);
int		is_num(char *s);

//!				TO REMOVE WHEN LIBFT IMPLANTED
int		ft_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, size_t n);
char	**ft_split(char const *str, char c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
//!				TO REMOVE WHEN LIBFT IMPLANTED

#endif