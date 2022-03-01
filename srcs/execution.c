/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:08:57 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/01 01:33:09 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern int	g_exit_status;

void	cmd_not_found(char **cmd, char **tmp_paths, char **env, t_cmd_lst *cmds)
{
	if (errno == EACCES)
	{
		error_manager(ERNO_ACCESS, cmd[0]);
		g_exit_status = 1;
	}
	else if (errno == ENOTDIR)
	{
		error_manager(ERNO_ISDIR, cmd[0]);
		g_exit_status = 126;
	}
	else if (!cmd[0] || cmd[0][0] == '\0')
	{
		ft_freetab(env);
		ft_freetab(cmd);
		ft_freetab(tmp_paths);
		rm_cmds(cmds);
		exit(g_exit_status);
	}
	else
	{
		error_manager(ERNO_NOCMD, cmd[0]);
		g_exit_status = 127;
	}
	ft_freetab(env);
	ft_freetab(cmd);
	ft_freetab(tmp_paths);
	rm_cmds(cmds);
	exit(g_exit_status);
}

void	ft_exec(char **cmd, char **envp, t_cmd_lst *cmds)
{
	int		i;
	char	**tmp_paths;
	char	*path;

	i = 0;
	if (!cmd[0] || cmd[0][0] == '\0' || ft_strcmp(cmd[0], "..") == 0
		|| ft_strcmp(cmd[0], ".") == 0)
		cmd_not_found(cmd, NULL, envp, cmds);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i])
	{
		if (cmd[0] && cmd[0][0] == '/' && access(cmd[0], X_OK) == 0)
			execve(cmd[0], cmd /*+ sizeof(char *)*/, envp);
		tmp_paths = ft_split(envp[i] + 5, ':');
		i = 0;
		while (tmp_paths[i])
		{
			path = get_path(tmp_paths[i], cmd[0]);
			//TODO ->PIPE g_exit_status
			if (cmd[0] && access(path, X_OK) == 0)
				execve(path, cmd, envp);
			i++;
			free(path);
			if (errno == EACCES)
				break ;
		}
	}
	cmd_not_found(cmd, tmp_paths, envp, cmds);
	//TODO ->PIPE g_exit_status
}

char	**get_cmd_str(t_cmd *cmd)
{
	int		i;
	char	**str_cmd;
	t_token	*tmp;

	i = 0;
	tmp = cmd->arg;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tmp = NULL;
	str_cmd = malloc(sizeof(char *) * (i + 1));
	str_cmd[i] = NULL;
	tmp = cmd->arg;
	i = 0;
	while (tmp)
	{
		str_cmd[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	return (str_cmd);
}

void	close_all_fds(int fd[6], t_cmd *cmd)
{
	if (cmd->next)
	{
		if (fd[0] != -1)
			close(fd[0]);
		if (fd[1] != -1)
			close(fd[1]);
	}
	if (fd[2] != -1)
		close(fd[2]);
	if (fd[3] != -1)
		close(fd[3]);
	if (fd[4] != -1)
		close(fd[4]);
}

void	execution(t_cmd *cmd, t_env *env, int fd[4], int is_piped,
	t_cmd_lst *cmds)
{
	char	**str_cmd;
	char	**env_arr;

	str_cmd = get_cmd_str(cmd);
	if (is_builtin(str_cmd[0]) && !is_piped)
	{
		close(fd[2]);
		close(fd[3]);
		ft_builtins(str_cmd, env, is_piped, cmds);
		return ;
	}
	cmd->pid = fork();
	if (cmd->pid < 0)
		ft_freetab(str_cmd);
	if (cmd->pid < 0)
		exit(errno);
	if (cmd->pid == 0)
	{
		close_all_fds(fd, cmd);
		if (is_builtin(str_cmd[0]))
			ft_builtins(str_cmd, env, is_piped, cmds);
		else
		{
			env_arr = env_cl_to_arr(env);
			ft_clear(env);
			ft_exec(str_cmd, env_arr, cmds);
		}
		ft_freetab(env_arr);
	}
	ft_freetab(str_cmd);
}
