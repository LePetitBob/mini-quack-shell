/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 05:44:00 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/24 03:46:04 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

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

void	free_one_token(t_token *token)
{
	free(token->str);
	free(token);
}

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
