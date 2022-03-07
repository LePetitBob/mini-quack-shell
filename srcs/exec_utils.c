/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 10:39:31 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/07 14:48:09 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

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

void	access_exec(char **cmd, char *path, char **envp)
{
	if (cmd[0] && access(path, X_OK) == 0)
		execve(path, cmd, envp);
}

void	free_exit(char **env, char **cmd, char **tmp_paths, t_cmd_lst *cmds)
{
	ft_freetab(env);
	ft_freetab(cmd);
	if (tmp_paths)
		ft_freetab(tmp_paths);
	rm_cmds(cmds);
	exit(g_status.exit_status);
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

int	last_hd(t_token *redir)
{
	t_token	*tmp;
	int		i;

	tmp = redir;
	i = 1;
	while (tmp)
	{
		if (tmp->next && tmp->next->type == HERE_DOC)
			i = 0;
		tmp = tmp->next;
	}
	return (i);
}
