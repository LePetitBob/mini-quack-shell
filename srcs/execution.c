/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:08:57 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/05 14:08:22 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

void	cmd_not_found(char **cmd, char **tmp_paths, char **env, t_cmd_lst *cmds)
{
	if (errno == EACCES)
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
		if (cmd[0][0] == '/')
			error_manager(ERNO_NOFILEDIR, cmd[0]);
		else
			error_manager(ERNO_NOCMD, cmd[0]);
		g_status.exit_status = 127;
	}
	ft_freetab(env);
	ft_freetab(cmd);
	if (tmp_paths)
		ft_freetab(tmp_paths);
	rm_cmds(cmds);
	exit(g_status.exit_status);
}

void	ft_exec(char **cmd, char **envp, t_cmd_lst *cmds)
{
	int		i;
	char	**tmp_paths;
	char	*path;

	i = 0;
	tmp_paths = NULL;
	if (!cmd[0] || cmd[0][0] == '\0' || ft_strcmp(cmd[0], "..") == 0
		|| ft_strcmp(cmd[0], ".") == 0)
		cmd_not_found(cmd, NULL, envp, cmds);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i])
	{
		if (cmd[0] && cmd[0][0] == '.' && access(cmd[0], X_OK) == 0)
			execve(cmd[0], cmd, envp);
		tmp_paths = ft_split(envp[i] + 5, ':');
		i = 0;
		while (tmp_paths[i])
		{
			path = get_path(tmp_paths[i], cmd[0]);
			if (cmd[0] && access(path, X_OK) == 0)
				execve(path, cmd, envp);
			i++;
			free(path);
			if (errno == EACCES)
				break ;
		}
	}
	cmd_not_found(cmd, tmp_paths, envp, cmds);
}

char	**get_cmd_str(t_cmd *cmd)
{
	int		i;
	char	**str_cmd;
	t_token	*tmp;

	if (!cmd->arg)
		return (NULL);
	i = 0;
	tmp = cmd->arg;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	str_cmd = malloc(sizeof(char *) * (i + 1));
	if (!str_cmd)
		return (NULL);
	str_cmd[i] = NULL;
	tmp = cmd->arg;
	i = -1;
	while (tmp)
	{
		str_cmd[++i] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	return (str_cmd);
}

void	close_all_fds(int fd[6], t_cmd *cmd)
{
	if (cmd->next)
	{
		close(fd[0]);
		close(fd[1]);
	}
	close(fd[2]);
	close(fd[3]);
	if (fd[4] != -1)
		close(fd[4]);
}

// int	here_docs(t_cmd_lst *cmds)
// {
// 	t_cmd	*cmd_tmp;
// 	t_token	*tkn_tmp;
// 	int		nb_hd;

// 	nb_hd = 0;
// 	cmd_tmp = cmds->first
// 	return (nb_hd);
// }

void	execution(t_cmd *cmd, t_env *env, int fd[6], t_cmd_lst *cmds)
{
	char	**str_cmd;
	char	**env_arr;
	// int		nb_hd;

	// nb_hd = here_docs(cmds);
	// if (nb_hd > 16)
	// 	ft_exit() //! 16+ hd --> quit (exit(2))
	str_cmd = get_cmd_str(cmd);
	if (!str_cmd || !str_cmd[0])
		return ;
	if (is_builtin(str_cmd[0]) && !fd[5])
	{
		close(fd[2]);
		close(fd[3]);
		ft_builtins(str_cmd, env, fd, cmds);
		return ;
	}
	cmd->pid = fork();
	g_status.pid = cmd->pid;
	if (cmd->pid < 0)
		ft_freetab(str_cmd);
	if (cmd->pid < 0)
		exit(errno);
	if (cmd->pid == 0)
	{
		redirection(cmd, fd);
		// abort_exec(cmd, cmds, env, fd);
		if (cmd->fdin == -1 || cmd->fdout == -1
			|| cmd->fdin == -2 || cmd->fdout == -2)
		{
			close(fd[2]);
			close(fd[3]);
			ft_freetab(str_cmd);
			rl_clear_history();
			ft_clear(env);
			rm_cmds(cmds);
			exit(g_status.exit_status);
		}
		// abort_exec(cmd, cmds, env, fd);
		close_all_fds(fd, cmd);
		if (is_builtin(str_cmd[0]) || !ft_strcmp(str_cmd[0], "echo"))
			ft_builtins(str_cmd, env, fd, cmds);
		else
		{
			env_arr = env_cl_to_arr(env);
			ft_clear(env);
			ft_exec(str_cmd, env_arr, cmds);
		}
	}
	ft_freetab(str_cmd);
}
