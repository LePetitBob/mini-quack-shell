/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:16:30 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/02 01:09:18 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern int	g_exit_status;

void	redir_out(t_cmd *cmd, char *str, int type, int *i)
{
	if (type == ROUT)
	{
		if (cmd->fdout != 1)
			close(cmd->fdout);
		if (!invalid_filename(str, "OUT", i))
			cmd->fdout = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			cmd->fdout = -1;
	}
	else if (type == DROUT)
	{
		if (cmd->fdout != 1)
			close(cmd->fdout);
		if (!invalid_filename(str, "OUT", i))
			cmd->fdout = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cmd->fdout = -1;
	}
}

void	apply_redir(char *str, int type, t_cmd *cmd, int *i)
{
	if (type == HERE_DOC)
	{
		if (cmd->fdin != 0)
			close(cmd->fdin);
		get_here_doc(str);
		cmd->fdin = open(HERE_DOC_PATH, O_RDONLY);
	}
	else if (type == RIN)
	{
		if (cmd->fdin != 0)
			close(cmd->fdin);
		if (!invalid_filename(str, "IN", i))
			cmd->fdin = open(str, O_RDONLY);
		else
			cmd->fdin = -1;
	}
	else if (type == ROUT || type == DROUT)
		redir_out(cmd, str, type, i);
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

void	redirection(t_cmd *cmd, int fd[6])
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = cmd->redir;
	while (tmp)
	{
		apply_redir(tmp->str, tmp->type, cmd, &i);
		if (i != 0)
			break ;
		tmp = tmp->next;
	}
	redir_pipe(cmd, fd);
	if (cmd->fdin != -1 && cmd->fdin != 0)
		dup2(cmd->fdin, STDIN_FILENO);
	if (cmd->fdin != -1 && cmd->fdin != 0)
		close(cmd->fdin);
	else if (cmd->fdin == -1)
		tmp_pipe(0);
	if (cmd->fdout != -1 && cmd->fdout != 1)
		dup2(cmd->fdout, STDOUT_FILENO);
	if (cmd->fdout != -1 && cmd->fdout != 1)
		close(cmd->fdout);
	else if (cmd->fdout == -1)
		tmp_pipe(1);
}
