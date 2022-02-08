/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:29:33 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/08 11:29:57 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ducklinclude/mini-quack-shell.h"

// typedef struct s_btn
// {
// 	char	*cmd;
// 	void	(*ft)(char **, t_env *);
// }t_btn;

// static const t_btn	g_btntab[] =
// {
// 	{"exit", &ft_exit},
// 	{"pwd", &ft_pwd},
// 	{NULL, NULL}
// };

void	ft_builtins(char **cmd, t_env *env)
{
	pid_t	pid;

	if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(cmd, env);
	else if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_env(env);
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(env, cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(env, cmd);
	else if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(cmd, env);
}