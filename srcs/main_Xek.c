/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_Xek.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:46:42 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/10 18:45:36 by vduriez          ###   ########.fr       */
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
	cmd->arg = create_token("echo", 0);
	cmd->arg->next = create_token("coucou", 2);
	cmds->first = cmd;

}

void	add_cmd2(t_cmd_lst *cmds)
{
	t_cmd	*cmd;

	cmd = create_cmd();
	cmd->arg = create_token("grep", 0);
	cmd->arg->next = create_token("r", 0);
	cmds->first->next = cmd;
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
			tkn2 = tmp->arg->next;
			free(tkn->str);
			free(tkn);
			tkn = tkn2;
		}
		tkn = tmp->redir;
		while (tkn)
		{
			tkn2 = tmp->redir->next;
			free(tkn->str);
			free(tkn);
			tkn = tkn2;
		}
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_cmd_lst	cmds;
	t_cmd		*tmp;
	// int			fdpipe[3];
	t_env		env;

	(void)ac;
	(void)av;
	(void)envp;
	cmds.first = NULL;
	get_env(envp, &env);
	add_cmd1(&cmds);
	// add_cmd2(&cmds);
	printf("cmd1 :\narg[0] : %s\narg[1] : %s\n\n", cmds.first->arg->str, cmds.first->arg->next->str);
	// printf("cmd2 :\narg[0] : %s\narg[1] : %s\n", cmds.first->next->arg->str, cmds.first->next->arg->next->str);
	tmp = cmds.first;
	// fdpipe[2] = dup(STDIN_FILENO);
	while (tmp)
	{
		// if (tmp->next)
		// 	pipe(fdpipe);
			//	^-- if (pipe < 0) clean stop
		// redir
		redir(tmp);
		// exec -> is builtin ? -> fork
		execution(tmp, &env);
		// if (tmp->next)
		// 	closepipe(fdpipe);
		// dup2(fdpipe[0], fdpipe[2]);
		tmp = tmp->next;
	}
	tmp = cmds.first;
	// while (tmp)
	// {
	// 	waitpid(tmp->pid, NULL, 0);
	// 	tmp = tmp->next;
	// }
	ft_clear(&env);
	rm_cmds(&cmds);
	return (0);
}