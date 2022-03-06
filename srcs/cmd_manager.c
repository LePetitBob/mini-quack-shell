/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 19:37:04 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/06 15:41:19 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

void	rm_cmds(t_cmd_lst *cmd)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;

	if (!cmd)
		return ;
	tmp = cmd->first;
	while (tmp)
	{
		tmp2 = tmp->next;
		clear_token_cl(tmp->arg);
		clear_token_cl(tmp->redir);
		free(tmp);
		tmp = tmp2;
	}
	free(cmd);
}

void	closepipe(int fd[3])
{
	if (fd[0] > -1)
		close(fd[0]);
	if (fd[1] > -1)
		close(fd[1]);
}

void	close_wait_clear(t_cmd_lst *cmds, int fd[6])
{
	t_cmd	*tmp;
	int		err;

	err = 0;
	dup2(fd[2], STDIN_FILENO);
	dup2(fd[3], STDOUT_FILENO);
	close(fd[2]);
	close(fd[3]);
	if (fd[4] > -1)
		close(fd[4]);
	tmp = cmds->first;
	while (tmp)
	{
		waitpid(tmp->pid, &err, 0);
		if (WIFEXITED(err) && tmp->arg && is_builtin(tmp->arg->str) == 0
			&& !tmp->next)
		{
			g_status.exit_status = WEXITSTATUS(err);
		}
		tmp = tmp->next;
	}
	rm_cmds(cmds);
}

void	init_values(int fd[6], t_cmd_lst *cmds, t_env *env, t_cmd *cmd)
{
	cmds->first = cmd;
	fd[5] = 0;
	if (cmds->first->next)
		fd[5] = 1;
	fd[4] = -1;
	get_over_here_docs(cmds, env, &fd[4]);
	fd[2] = dup(STDIN_FILENO);
	fd[3] = dup(STDOUT_FILENO);
	g_status.pid = -1;
}

//here: fd[0] is unset; becomes pipe(0)
//here: fd[1] is unset; becomes pipe(1)
//here: fd[2]=STDIN
//here: fd[3]=STDOUT
//here: fd[4] is unset; it will take fd[0]'s value which is garbagge memory
//here: fd[5] is an int; 0=ONE cmd | 1=MULTIPLE cmd
void	cmd_manager(t_env *env, t_cmd *cmd)
{
	t_cmd_lst	*cmds;
	t_cmd		*tmp;
	int			fd[6];

	cmds = malloc(sizeof(t_cmd *));
	init_values(fd, cmds, env, cmd);
	tmp = cmds->first;
	while (tmp && fd[4] != -2)
	{
		g_status.pid = -1;
		if (tmp->prev)
		{
			if (fd[4] == -1)
				fd[4] = dup(fd[0]);
			else
				dup2(fd[0], fd[4]);
			closepipe(fd);
		}
		if (tmp->next)
			pipe(fd);
		execution(tmp, env, fd, cmds);
		tmp = tmp->next;
	}
	close_wait_clear(cmds, fd);
}
