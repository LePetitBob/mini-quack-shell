/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:16:30 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/23 04:37:40 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern int	g_exit_status;

int	invalid_filename(char *filename, char *FILENO, int *i)
{
	if (!access(filename, F_OK))
	{
		if ((!ft_strcmp(FILENO, "OUT") && !access(filename, W_OK))
			|| (!ft_strcmp(FILENO, "IN") && !access(filename, R_OK)))
			return (0);
		*i = 1;
		write(2, "mini-quack-shell: ", 18);
		write(2, filename, ft_strlen(filename));
		write(2, ": permission denied\n", 20);
		g_exit_status = 1;
		return (1);
	}
	else if (!ft_strcmp(FILENO, "IN"))
	{
		*i = 1;
		write(2, "mini-quack-shell: no such file or directory: ", 45);
		write(2, filename, ft_strlen(filename));
		write(2, "\n", 1);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

void	redir_out(t_cmd *cmd, char *str, int type, int *i)
{
	if (type == ROUT)
	{
		if (cmd->fdout != 1)
			close(cmd->fdout);
		if (!invalid_filename(str, "OUT", i))
			cmd->fdout = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (type == DROUT)
	{
		if (cmd->fdout != 1)
			close(cmd->fdout);
		if (!invalid_filename(str, "OUT", i))
			cmd->fdout = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
	}
	else if (type == ROUT || type == DROUT)
		redir_out(cmd, str, type, i);
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
	if (cmd->prev)
		dup2(fd[4], STDIN_FILENO);
	if (cmd->next)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(fd[3], STDOUT_FILENO);
	if (cmd->fdin != 0)
		dup2(cmd->fdin, STDIN_FILENO);
	if (cmd->fdin != 0)
		close(cmd->fdin);
	if (cmd->fdout != 1)
		dup2(cmd->fdout, STDOUT_FILENO);
	if (cmd->fdout != 1)
		close(cmd->fdout);
}
