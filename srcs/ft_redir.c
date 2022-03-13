/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:16:30 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/13 20:30:04 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

void	redir_out(t_cmd *cmd, char *str, int type, int *i)
{
	if (type == ROUT)
	{
		if (cmd->fdout > 1)
			close(cmd->fdout);
		if (!invalid_filename(str, "OUT", i))
			cmd->fdout = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			cmd->fdout = -2;
	}
	else if (type == DROUT)
	{
		if (cmd->fdout > 1)
			close(cmd->fdout);
		if (!invalid_filename(str, "OUT", i))
			cmd->fdout = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cmd->fdout = -2;
	}
	if (cmd->fdout == -1 && errno == EISDIR)
		error_manager(ERNO_ISDIR, str);
}

void	apply_redir(t_token *tmp, t_cmd *cmd, int *i, int pipe_hd[2])
{
	if (tmp->type == HERE_DOC)
	{
		if (cmd->fdin > 0)
			close(cmd->fdin);
		if (last_hd(tmp))
			write(pipe_hd[1], tmp->str, ft_strlen(tmp->str));
		cmd->fdin = -42;
	}
	else if (tmp->type == RIN)
	{
		if (cmd->fdin > 0)
			close(cmd->fdin);
		if (!invalid_filename(tmp->str, "IN", i))
			cmd->fdin = open(tmp->str, O_RDONLY);
		else
			cmd->fdin = -2;
	}
	else if ((tmp->type == ROUT || tmp->type == DROUT)
		&& ((ft_strcmp(tmp->str, "/dev/stdout")
				&& ft_strcmp(tmp->str, "/dev/fd/1"))
			|| ((!ft_strcmp(tmp->str, "/dev/stdout")
					|| !ft_strcmp(tmp->str, "/dev/fd/1"))
				&& !tmp->next && !cmd->next)))
		redir_out(cmd, tmp->str, tmp->type, i);
}

void	tmp_pipe(int std)
{
	int	tmppipe[2];

	pipe(tmppipe);
	dup2(tmppipe[std], std);
	close(tmppipe[1]);
	close(tmppipe[0]);
}

void	redir_pipe(t_cmd *cmd, int fd[6])
{
	if (cmd->prev)
		dup2(fd[4], STDIN_FILENO);
	if (cmd->next)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(fd[3], STDOUT_FILENO);
}

void	check_all_redirs(t_cmd *cmd, int pipe_hd[2])
{
	if (cmd->fdin > 0)
		dup2(cmd->fdin, STDIN_FILENO);
	if (cmd->fdin > 0)
		close(cmd->fdin);
	else if (cmd->fdin == -42)
		dup2(pipe_hd[0], STDIN_FILENO);
	else if (cmd->fdin == -2)
		tmp_pipe(0);
	close(pipe_hd[0]);
	close(pipe_hd[1]);
	if (cmd->fdout > 1)
		dup2(cmd->fdout, STDOUT_FILENO);
	if (cmd->fdout > 1)
		close(cmd->fdout);
	else if (cmd->fdout == -2)
		tmp_pipe(1);
}
