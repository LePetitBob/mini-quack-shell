/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:29:33 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/22 14:26:56 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	ft_builtins(char **cmd, t_env *env, int is_piped)
{
	if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(cmd, env, is_piped);
	else if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd();
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
	if (is_piped)
	{
		rl_clear_history();
		ft_clear(env);
		exit(0); //! g_exit_status
	}
}
