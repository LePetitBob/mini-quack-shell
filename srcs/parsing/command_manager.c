/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:41:11 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/23 00:17:53 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	command_manager(t_token *tokens, t_env *env)
{
	t_token	*it_t;
	t_cmd	*cmds;
	t_cmd	*it_c;

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
			if (it_t && (it_t->type == RIN || it_t->type == ROUT
					|| it_t->type == DROUT || it_t->type == HERE_DOC))
				assign_token_cmd(&it_c, &it_t, 0);
			if (it_t && it_t->type == WORD)
				assign_token_cmd(&it_c, &it_t, 1);
		}
	}
	// print_cmds(cmds);
	cmd_manager(env, cmds);
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

void	assign_token_cmd(t_cmd **it_c, t_token **it_t, int assign)
{
	t_token	*tmp;

	if (assign == 0)
		tmp = (*it_c)->redir;
	else if (assign == 1)
		tmp = (*it_c)->arg;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (*it_t);
		(*it_t)->prev = tmp;
		tmp = tmp->next;
	}
	else
	{
		if (assign == 0)
			(*it_c)->redir = *it_t;
		else if (assign == 1)
			(*it_c)->arg = *it_t;
		tmp = *it_t;
	}
	unlink_cmd_token(tmp, it_t);
}

void	unlink_cmd_token(t_token *cmd_t, t_token **it_t)
{
	*it_t = (*it_t)->next;
	if (*it_t)
	{
		cmd_t->next = NULL;
		(*it_t)->prev = NULL;
	}
}
