/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 19:37:04 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/24 17:51:12 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern int	g_exit_status;

void	clear_token_cl(t_token *lst)
{
	t_token	*tkn;
	t_token	*tkn2;

	tkn = lst;
	while (tkn)
	{
		tkn2 = tkn->next;
		free(tkn->str);
		free(tkn);
		tkn = tkn2;
	}
}

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
	close(fd[0]);
	close(fd[1]);
}

void	close_wait_clear(t_cmd_lst *cmds, int fd[6], t_env *env)
{
	t_cmd	*tmp;
	int		err;

	err = 0;
	dup2(fd[2], STDIN_FILENO);
	dup2(fd[3], STDOUT_FILENO);
	close(fd[2]);
	close(fd[3]);
	tmp = cmds->first;
	while (tmp)
	{
		waitpid(tmp->pid, &err, 0);
		if (err != 0 && g_exit_status != 0)
			g_exit_status = 1;
		tmp = tmp->next;
	}
	rm_cmds(cmds);
	rm_here_doc_tmp_file(env);
}

void	cmd_manager(t_env *env, t_cmd *cmd)
{
	t_cmd_lst	*cmds;
	t_cmd		*tmp;
	int			fd[6];

	cmds = malloc(sizeof(t_cmd *));
	cmds->first = cmd;
	fd[5] = 0;
	if (cmds->first->next)
		fd[5] = 1;
	tmp = cmds->first;
	fd[2] = dup(STDIN_FILENO);
	fd[3] = dup(STDOUT_FILENO);
	fd[4] = dup(STDIN_FILENO);
	while (tmp)
	{
		if (tmp->prev)
			dup2(fd[0], fd[4]);
		if (tmp->prev)
			closepipe(fd);
		if (tmp->next)
			pipe(fd);
		redirection(tmp, fd);
		execution(tmp, env, fd, fd[5]);
		tmp = tmp->next;
	}
	close_wait_clear(cmds, fd, env);
}
