/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:08:57 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/24 01:22:39 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern int	g_exit_status;

void	cmd_not_found(char *cmd, char **tmp_paths)
{
	if (errno == EACCES)
	{
		write(2, "mini-quack-shell: permission denied: ", 37);
		write(2, cmd, ft_strlen(cmd));
		write(2, "\n", 1);
		g_exit_status = 1;
	}
	else
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
		g_exit_status = 127;
	}
	ft_freetab(tmp_paths);
	exit(g_exit_status);
}

void	ft_exec(char **cmd, char **envp)
{
	int		i;
	char	**tmp_paths;
	char	*path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i])
	{
		if (access(cmd[0], X_OK) == 0)
			execve(cmd[0], cmd + sizeof(char *), envp);
		tmp_paths = ft_split(envp[i] + 5, ':');
		i = 0;
		while (tmp_paths[i])
		{
			path = get_path(tmp_paths[i], cmd[0]);
			if (access(path, X_OK) == 0)
				execve(path, cmd, envp);
			i++;
			free(path);
			if (errno == EACCES)
				break ;
		}
	}
	cmd_not_found(cmd[0], tmp_paths);
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

//here: fd[0] is unset; his value is gabagge memory
//here: fd[1] is unset; his value is gabagge memory
//here: fd[2]=STDIN
//here: fd[3]=STDOUT
void	close_all_fds(int fd[4], t_cmd *cmd)
{
	if (cmd->next)
	{
		close(fd[0]);
		close(fd[1]);
	}
	close(fd[2]);
	close(fd[3]);
}

void	execution(t_cmd *cmd, t_env *env, int fd[4], int is_piped)
{
	char	**str_cmd;
	char	**env_arr;

	str_cmd = get_cmd_str(cmd);
	if (is_builtin(str_cmd[0]) && !is_piped)
		ft_builtins(str_cmd, env, is_piped);
	if (is_builtin(str_cmd[0]) && !is_piped)
		return ;
	cmd->pid = fork();
	if (cmd->pid < 0)
		ft_freetab(str_cmd);
	if (cmd->pid < 0)
		exit(errno);
	if (!cmd->pid)
	{
		close_all_fds(fd, cmd);
		if (is_builtin(str_cmd[0]))
			ft_builtins(str_cmd, env, is_piped);
		else
		{
			env_arr = env_cl_to_arr(env);
			ft_clear(env);
			ft_exec(str_cmd, env_arr);
		}
		ft_freetab(str_cmd);
		ft_freetab(env_arr);
	}
}
