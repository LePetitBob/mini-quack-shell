/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini-quack-shell.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:52:38 by vduriez           #+#    #+#             */
/*   Updated: 2022/01/31 16:55:29 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_QUACK_SHELL
# define MINI_QUACK_SHELL
# include <stdio.h>
# include <stdlib.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>

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
void	ft_pwd(void);
void	ft_cd(char *newpath, char **envp);
void	ft_echo(char **s);
void	ft_env(t_env *env);
void	get_env(char **envp, t_env *env);
void	ft_exit(int	*exit_shell, t_env *env);
//?			Builtins

//			CL
t_env_var	*ft_create_elem(char *name, char *value);
void		ft_addfirst(t_env *env, char *name, char *value);
void		ft_addlast(t_env *env, char *name, char *value);
void		ft_rmfirst(t_env *env);
void		ft_rmlast(t_env *env);
//			CL

void	ft_free(char **s);


//!				TO REMOVE WHEN LIBFT IMPLANTED
int		ft_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *str, char c);
//!				TO REMOVE WHEN LIBFT IMPLANTED

#endif