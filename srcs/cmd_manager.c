/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2022/02/22 19:37:04 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/22 19:38:16 by amarini-         ###   ########.fr       */
=======
/*   Created: 2022/02/19 05:52:03 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/22 21:50:13 by vduriez          ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

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

void	init_fds(int fd[4])
{
	fd[2] = dup(STDIN_FILENO);
	fd[3] = dup(STDOUT_FILENO);
}

void	close_wait_clear(t_cmd_lst *cmds, t_env *env)
{
	t_cmd	*tmp;

	// close(fd[2]);
	// close(fd[3]);
	tmp = cmds->first;
	while (tmp)
	{
		waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
	rm_cmds(cmds);
	rm_here_doc_tmp_file(env);
}

void	cmd_manager(t_env *env, t_cmd *cmd)
{
	t_cmd_lst	*cmds;
	t_cmd		*tmp;
	int			fd[5];
	int			is_piped;

	cmds = malloc(sizeof(t_cmd*));
	cmds->first = cmd;
	is_piped = 0;
	if (cmds->first->next)
		is_piped = 1;
	tmp = cmds->first;
	// init_fds(&fd);
	fd[2] = dup(STDIN_FILENO);
	fd[3] = dup(STDOUT_FILENO);
	while (tmp)
	{
		if (tmp->prev)
		{
			dup2(fd[0], fd[4]);
			closepipe(fd);
		}
		if (tmp->next)
			pipe(fd);
		redirection(tmp, fd);
		execution(tmp, env, fd, is_piped);
<<<<<<< HEAD
		if (tmp->next)
		{
			dup2(fd[0], fd[2]);
			closepipe(fd);
		}
		dup2(fd[3], STDOUT_FILENO);
=======
>>>>>>> master
		tmp = tmp->next;
	}
	dup2(fd[2], STDIN_FILENO);
	dup2(fd[3], STDOUT_FILENO);
	close(fd[2]);
	close(fd[3]);
	close_wait_clear(cmds, env);
}
