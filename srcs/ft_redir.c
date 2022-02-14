/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:16:30 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/14 16:51:56 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	redir(t_cmd *cmd, int fd[4])
{
	t_token	*tmp;
	int		err;

	err = 0;
	tmp = cmd->redir;
	if (cmd->prev)
		dup2(fd[2], STDIN_FILENO);
	if (cmd->next)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(fd[3], STDOUT_FILENO);
	while (tmp)
	{
		// if (tmp->type == HERE_DOC)
		// {
			// cmd->fdin = open(tmp->str, O_RDONLY);
			// dup2(cmd->fdin, STDIN_FILENO);
			// close(cmd->fdin);
		// }
		if (tmp->type == RIN)
		{
			//TODO check errors with access
			cmd->fdin = open(tmp->str, O_RDONLY);
			dup2(cmd->fdin, STDIN_FILENO);
			close(cmd->fdin);
		}
		else if (tmp->type == ROUT)
		{
			//TODO check errors with access
			cmd->fdout = open(tmp->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			dup2(cmd->fdout, STDOUT_FILENO);
			close(cmd->fdout);
		}
		else if (tmp->type == DROUT)
		{
			//TODO check errors with access
			cmd->fdout = open(tmp->str, O_RDWR | O_APPEND | O_CREAT, 0644);
			dup2(cmd->fdout, STDOUT_FILENO);
			close(cmd->fdout);
		}
		else if (err)
			break ;
		tmp = tmp->next;
	}
}