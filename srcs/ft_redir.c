/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:16:30 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/16 15:41:49 by vduriez          ###   ########.fr       */
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
	else
	{
		*err = 1;
		write(2, "mini-quack-shell: no such file or directory: ", 45);
		write(2, filename, ft_strlen(filename));
		write(2, "\n", 1);
		return (1);
	}
}

void	check_redir_IN(int *err, char *filename, int fd)
{
	if (invalid_filename(filename, err, "IN"))
		return ;
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	check_redir_OUT(int *err, char *filename, int fd)
{
	if (invalid_filename(filename, err, "OUT"))
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirection(t_cmd *cmd, int fd[4])
{
	t_token	*tmp;
	int		err;

	err = 0;
	tmp = cmd->redir;
	if (cmd->prev)
		dup2(fd[2], STDIN_FILENO);
	if (cmd->next)
		dup2(fd[1], STDOUT_FILENO);
	else if (cmd->prev)
		dup2(fd[3], STDOUT_FILENO);
	while (tmp)
	{
		// if (tmp->type == HERE_DOC)
		if (tmp->type == RIN)
		{
			cmd->fdin = open(tmp->str, O_RDONLY);
			check_redir_IN(&err, tmp->str, cmd->fdin);
		}
		else if (tmp->type == ROUT)
		{
			cmd->fdout = open(tmp->str, O_WRONLY | O_CREAT | O_TRUNC);
			check_redir_OUT(&err, tmp->str, cmd->fdout);
		}
		else if (tmp->type == DROUT)
		{
			cmd->fdout = open(tmp->str, O_WRONLY | O_CREAT | O_APPEND);
			check_redir_OUT(&err, tmp->str, cmd->fdout);
		}
		if (err)
			break ;
		tmp = tmp->next;
	}
}
