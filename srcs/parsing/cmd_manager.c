/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:41:11 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/17 19:57:37 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	command_manager(t_token *tokens, t_env *env)
{
	t_token	*it_t;
	t_cmd	*cmds;
	t_cmd	*it_c;

	(void)env;
	link_fd_redir(&tokens);
	ft_putstr("\n_____merge_redir:\n");
	print_tokens(tokens);
	printf("\n");
	it_t = tokens;
	cmds = ft_create_cmd();
	it_c = cmds;
	while (it_t)
	{
		// printf("it-[%s]\n", it_t->str);
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
					it_c->redir->next = it_t;
					it_t->prev = it_c->redir;
				}
				else
					it_c->redir = it_t;
				if (it_t->next)
				{
					it_t = it_t->next;
					it_t->prev->next = NULL;
					it_t->prev = NULL;
				}
			}
			if (it_t->type == WORD)
			{
				it_c->arg = it_t;
				while (it_t->next && it_t->next->type == WORD)
					it_t = it_t->next;
				if (it_t->next)
				{
					it_t = it_t->next;
					it_t->prev->next = NULL;
					it_t->prev = NULL;
				}
			}
			// printf("it-[%s]\n", it_t->str);
			if (it_t->type != PIPE)
				it_t = it_t->next;
		}
		// it_t = it_t->next;
	}
	ft_putstr("\n_____cmds:\n");
	print_cmds(cmds);
	printf("\n");
	//call vincent functions
}

void	link_fd_redir(t_token **tokens)
{
	t_token	*it;
	t_token	*tmp;

	it = *tokens;
	while (it->next)
	{
		printf("it-[%s]\n", it->str);
		if ((it->next->type == FD || it->next->type == LIMITER)
			&& (it->type == RIN || it->type == ROUT || it->type == DROUT
			|| it->type == HERE_DOC))
		{
			tmp = it;
			it = it->next;
			it->type = tmp->type;
			printf("it-[%s]\n", it->str);
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
			printf("it-[%s]\n", it->str);
			// tmp = NULL;
		}
		else
			it = it->next;
	}
}
