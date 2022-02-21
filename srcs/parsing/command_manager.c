/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:41:11 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/21 16:35:44 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

t_cmd	*ft_create_cmd(void)
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

void	command_manager(t_token *tokens, t_env *env)
{
	t_token	*it_t;
	t_cmd	*cmds;
	t_cmd	*it_c;
	t_token	*tmp;

	(void)env;
	link_fd_redir(&tokens);
	it_t = tokens;
	cmds = ft_create_cmd();
	it_c = cmds;
	while (it_t)
	{
		if (it_t->type == PIPE)
		{
			it_c->next = ft_create_cmd();
			it_c->next->prev = it_c;
			it_c = it_c->next;
			it_t = it_t->next;
			free(it_t->prev->str);
			free(it_t->prev);
			it_t->prev = NULL;
		}
		while (it_t && it_t->type != PIPE)
		{
			if (it_t->type == RIN || it_t->type == ROUT || it_t->type == DROUT
				|| it_t->type == HERE_DOC)
			{
				if (it_c->redir)
				{
					tmp = it_c->redir;
					while (tmp->next)
						tmp = tmp->next;
					tmp->next = it_t;
					it_t->prev = tmp;
					tmp = tmp->next;
				}
				else
				{
					it_c->redir = it_t;
					tmp = it_c->redir;
				}
				if (it_t->next)
				{
					it_t = it_t->next;
					tmp->next = NULL;
					it_t->prev = NULL;
				}
				else
					it_t = it_t->next;
			}
			if (it_t->type == WORD)
			{
				if (it_c->arg)
				{
					tmp = it_c->arg;
					while (tmp->next)
						tmp = tmp->next;
					tmp->next = it_t;
					it_t->prev = tmp;
					tmp = tmp->next;
				}
				else
				{
					it_c->arg = it_t;
					tmp = it_c->arg;
				}
				if (it_t->next)
				{
					it_t = it_t->next;
					tmp->next = NULL;
					it_t->prev = NULL;
				}
				else
					it_t = it_t->next;
			}
		}
	}
	print_cmds(cmds);
<<<<<<< HEAD:srcs/parsing/command_manager.c
=======
	printf("\n");
	cmd_manager(env, cmds);
>>>>>>> 79230b949c7516644ad3b11c02315a10c170ac7a:srcs/parsing/command_manager.c
}

void	link_fd_redir(t_token **tokens)
{
	t_token	*it;
	t_token	*tmp;

	it = *tokens;
	while (it->next)
	{
		if ((it->next->type == FD || it->next->type == LIMITER)
			&& (it->type == RIN || it->type == ROUT || it->type == DROUT
				|| it->type == HERE_DOC))
		{
			tmp = it;
			it = it->next;
			it->type = tmp->type;
			if (tmp->prev)
			{
				it->prev = tmp->prev;
				tmp->prev->next = it;
			}
			else
			{
				it->prev = NULL;
				*tokens = it;
			}
			free(tmp->str);
			free(tmp);
		}
		else
			it = it->next;
	}
}
