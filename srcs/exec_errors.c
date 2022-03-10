/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 07:54:48 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/10 12:39:40 by amarini-         ###   ########.fr       */
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

void	cmd_not_found(char **cmd, char **tmp_paths, char **env, t_cmd_lst *cmds)
{
	if (cmd[0] && cmd[0][0] != '\0' && (ft_strcmp(cmd[0], "/") == 0
			|| check_for_directory(cmd[0]) == 0))
		send_error_msg(cmd[0], ERNO_ISDIR, 126);
	else if (errno == EACCES)
		send_error_msg(cmd[0], ERNO_ACCESS, 1);
	else if (ft_strcmp(cmd[0], ".") == 0)
		send_error_msg(cmd[0], ERNO_NOEXEC, 2);
	else
	{
		if (/*!find_in_env_arr(env) || */(cmd[0][0] == '.' && cmd[0][1] == '/')
			/*|| (!access(cmd[0], F_OK) && ft_strcmp(cmd[0], "$") == 1)*/)
			send_error_msg(cmd[0], ERNO_NOFILEDIR, 127);
		else
			send_error_msg(cmd[0], ERNO_NOCMD, 127);
	}
	free_exit(env, cmd, tmp_paths, cmds);
}
