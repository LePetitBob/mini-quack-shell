/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 07:54:48 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/06 19:47:20 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

void	abort_exec(char **cmd, t_cmd_lst *cmds, t_env *env, int fd[6])
{
	close(fd[2]);
	close(fd[3]);
	ft_freetab(cmd);
	rl_clear_history();
	ft_clear(env);
	rm_cmds(cmds);
	exit(g_status.exit_status);
}

void	apply_exec(char **str_cmd, int fd[6], t_env *env, t_cmd_lst *cmds)
{
	char	**env_arr;

	if (is_builtin(str_cmd[0]) || !ft_strcmp(str_cmd[0], "echo"))
		ft_builtins(str_cmd, env, fd, cmds);
	else
	{
		env_arr = env_cl_to_arr(env);
		ft_clear(env);
		ft_exec(str_cmd, env_arr, cmds);
	}
}

void	no_cmd(char **cmd, char **envp, t_cmd_lst *cmds)
{
	if (!cmd[0] || cmd[0][0] == '\0' || ft_strcmp(cmd[0], "..") == 0
		|| ft_strcmp(cmd[0], ".") == 0)
		cmd_not_found(cmd, NULL, envp, cmds);
}

void	failed_fork(t_cmd *cmd, char **str_cmd)
{
	if (cmd->pid < 0)
		ft_freetab(str_cmd);
	if (cmd->pid < 0)
		exit(errno);
}


int	find_in_env_arr(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5))
		i++;
	if (!envp[i])
		return (0);
	return (1);
}

void	cmd_not_found(char **cmd, char **tmp_paths, char **env, t_cmd_lst *cmds)
{
	if (ft_strcmp(cmd[0], "/") == 0)
		error_manager(ERNO_ISDIR, cmd[0]);
	if (ft_strcmp(cmd[0], "/") == 0)
		g_status.exit_status = 126;
	else if (errno == EACCES)
	{
		error_manager(ERNO_ACCESS, cmd[0]);
		g_status.exit_status = 1;
	}
	else if (ft_strcmp(cmd[0], ".") == 0)
	{
		error_manager(ERNO_NOEXEC, cmd[0]);
		g_status.exit_status = 2;
	}
	else
	{
		if (!find_in_env_arr(env) || (!access(cmd[0], F_OK) && ft_strcmp(cmd[0], "$") == 1))
			error_manager(ERNO_NOFILEDIR, cmd[0]);
		else
			error_manager(ERNO_NOCMD, cmd[0]);
		g_status.exit_status = 127;
	}
	free_exit(env, cmd, tmp_paths, cmds);
}
