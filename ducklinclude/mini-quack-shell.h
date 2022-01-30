/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini-quack-shell.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:52:38 by vduriez           #+#    #+#             */
/*   Updated: 2022/01/30 17:27:23 by vduriez          ###   ########.fr       */
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

//? Builtins
void	ft_pwd(char **envp);
void	ft_cd(char *newpath, char **envp);
void	ft_echo(int n, char *s);
void	ft_env(char **envp);
//? Builtins

void	ft_free(char **s);


//!				TO REMOVE WHEN LIBFT IMPLANTED
int		ft_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
//!				TO REMOVE WHEN LIBFT IMPLANTED

#endif