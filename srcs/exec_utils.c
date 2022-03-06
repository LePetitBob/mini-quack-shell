/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 10:39:31 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/06 10:52:47 by vduriez          ###   ########.fr       */
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
