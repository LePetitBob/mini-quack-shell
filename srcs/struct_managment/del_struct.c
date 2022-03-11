/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 05:44:00 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/11 17:13:06 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*it_c;

	it_c = cmds;
	while (it_c->next)
	{
		it_c = it_c->next;
		free_token(it_c->prev->arg);
		free_token(it_c->prev->redir);
		free(it_c->prev);
	}
	free_token(it_c->arg);
	free_token(it_c->redir);
	free(it_c);
}

void	free_one_token(t_token *token)
{
	free(token->str);
	free(token);
}

void	free_token(t_token *tokens)
{
	t_token	*it;

	it = tokens;
	while (it->next)
	{
		it = it->next;
		it->prev->next = NULL;
		free_one_token(it->prev);
		it->prev = NULL;
	}
	free(it->str);
	free(it);
	it = NULL;
}

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
