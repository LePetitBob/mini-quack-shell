/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_Xek.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:46:42 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/14 18:05:47 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	new->arg = NULL;
	new->redir = NULL;
	new->fdin = 0;
	new->fdout = 1;
	new->pid = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*create_token(char *str, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->str = ft_strdup(str);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_cmd1(t_cmd_lst *cmds)
{
	t_cmd	*cmd;

	cmd = create_cmd();
	cmd->arg = create_token("cat", 0);
	cmd->arg->next = create_token("coucou", 2);
	// cmd->redir = create_token("outfilr", 6);
	cmds->first = cmd;
}

void	add_cmd2(t_cmd_lst *cmds)
{
	t_cmd	*cmd;

	cmd = create_cmd();
	cmd->arg = create_token("grep", 0);
	cmd->arg->next = create_token("a", 0);
	// cmd->redir = create_token("outfilr", 6);
	cmd->prev = cmds->first;
	cmds->first->next = cmd;
}

void	add_cmd3(t_cmd_lst *cmds)
{
	t_cmd	*cmd;

	cmd = create_cmd();
	cmd->arg = create_token("grep", 0);
	cmd->arg->next = create_token("s", 0);
	cmd->redir = create_token("outfilr", 6);
	cmd->prev = cmds->first->next;
	cmds->first->next->next = cmd;
}

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

void	closepipe(int fd[3])
{
	close(fd[0]);
	close(fd[1]);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd_lst	cmds;
	t_cmd		*tmp;
	int			fd[4];
	t_env		env;

	(void)ac;
	(void)av;
	cmds.first = NULL;
	get_env(envp, &env);
	add_cmd1(&cmds);
	add_cmd2(&cmds);
	add_cmd3(&cmds);
	tmp = cmds.first;
	fd[2] = dup(STDIN_FILENO);
	fd[3] = dup(STDOUT_FILENO);
	while (tmp)
	{
		if (tmp->next)
			pipe(fd);
		//TODO	^--if (pipe < 0) clean stop
		redirection(tmp, fd);
		execution(tmp, &env, fd);
		if (tmp->next)
			dup2(fd[0], fd[2]);
		closepipe(fd);
		tmp = tmp->next;
	}
	close(fd[2]);
	close(fd[3]);
	tmp = cmds.first;
	while (tmp)
	{
		waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
	ft_clear(&env);
	rm_cmds(&cmds);
	return (0);
}