/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:16:30 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/18 18:23:01 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

int	invalid_filename(char *filename, int *err, char *FILENO)
{
	if (!access(filename, F_OK))
	{
		if ((!ft_strcmp(FILENO, "OUT") && !access(filename, W_OK))
			|| (!ft_strcmp(FILENO, "IN") && !access(filename, R_OK)))
			return (0);
		*err = 1;
		write(2, "mini-quack-shell: ", 18);
		write(2, filename, ft_strlen(filename));
		write(2, ": permission denied\n", 20);
		return (1);
	}
	else if (!ft_strcmp(FILENO, "IN"))
	{
		*err = 1;
		write(2, "mini-quack-shell: no such file or directory: ", 45);
		write(2, filename, ft_strlen(filename));
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}

void	redirection(t_cmd *cmd, int fd[4])
{
	t_token	*tmp;
	int		err;

	err = 0;
	tmp = cmd->redir;
	dup2(fd[2], STDIN_FILENO);
	if (cmd->next)
		dup2(fd[1], STDOUT_FILENO);
	else if (cmd->prev)
		dup2(fd[3], STDOUT_FILENO);
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
		{
			if (cmd->fdin != 0)
				close(cmd->fdin);
			get_here_doc(tmp->str);
			cmd->fdin = open(HERE_DOC_PATH, O_RDONLY);
		}
		else if (tmp->type == RIN)
		{
			if (cmd->fdin != 0)
				close(cmd->fdin);
			if (!invalid_filename(tmp->str, &err, "IN"))
				cmd->fdin = open(tmp->str, O_RDONLY);
		}
		else if (tmp->type == ROUT)
		{
			if (cmd->fdout != 1)
				close(cmd->fdout);
			if (!invalid_filename(tmp->str, &err, "OUT"))
				cmd->fdout = open(tmp->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (tmp->type == DROUT)
		{
			if (cmd->fdout != 1)
				close(cmd->fdout);
			if (!invalid_filename(tmp->str, &err, "OUT"))
				cmd->fdout = open(tmp->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if (err)
			break ;
		tmp = tmp->next;
	}
	if (cmd->fdin != 0)
	{
		dup2(cmd->fdin, STDIN_FILENO);
		close(cmd->fdin);
	}
	if (cmd->fdout != 1)
	{
		dup2(cmd->fdout, STDOUT_FILENO);
		close(cmd->fdout);
	}
}
