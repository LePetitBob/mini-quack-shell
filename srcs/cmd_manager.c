/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 05:52:03 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/19 05:57:56 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	rm_cmds(t_cmd_lst *cmd)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;
	t_token	*tkn;
	t_token	*tkn2;

	if (!cmd)
		return ;
	tmp = cmd->first;
	while (tmp)
	{
		tkn = tmp->arg;
		while (tkn)
		{
			tkn2 = tkn->next;
			free(tkn->str);
			free(tkn);
			tkn = tkn2;
		}
		tkn = tmp->redir;
		while (tkn)
		{
			tkn2 = tkn->next;
			free(tkn->str);
			free(tkn);
			tkn = tkn2;
		}
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

void	rm_here_doc_tmp_file(t_env *env)
{
	pid_t		pidtmp;
	char		*tmp[3];
	char		**tmpenv;

	tmpenv = env_cl_to_arr(env);
	if (access(HERE_DOC_PATH, F_OK) == 0)
	{
		pidtmp = fork();
		if (!pidtmp)
		{
			tmp[0] = ft_strdup("rm");
			tmp[1] = ft_strdup(HERE_DOC_PATH);
			tmp[2] = NULL;
			ft_exec(tmp, tmpenv);
		}
	}
}

void	closepipe(int fd[3])
{
	close(fd[0]);
	close(fd[1]);
}

void	cmd_manager(t_env *env, t_cmd_lst *cmds)
{
	t_cmd		*tmp;
	int			fd[4];
	int			is_piped;

	is_piped = 0;
	if (cmds->first->next)
		is_piped = 1;
	tmp = cmds->first;
	fd[2] = dup(STDIN_FILENO);
	fd[3] = dup(STDOUT_FILENO);
	while (tmp)
	{
		if (tmp->next)
			pipe(fd);
		redirection(tmp, fd);
		execution(tmp, env, fd, is_piped);
		if (tmp->next)
		{
			dup2(fd[0], fd[2]);
			closepipe(fd);
		}
		tmp = tmp->next;
	}
	close(fd[2]);
	close(fd[3]);
	tmp = cmds->first;
	while (tmp)
	{
		waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
	ft_clear(&env);
	rm_cmds(&cmds);
	rm_here_doc_tmp_file(env);
}