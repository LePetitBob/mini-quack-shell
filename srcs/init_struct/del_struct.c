/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 05:44:00 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/19 05:52:44 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	free_token(t_token *tokens)
{
	t_token	*it;

	it = tokens;
	while (tokens->next)
	{
		it = it->next;
		free(it->prev->str);
		it->prev->next = NULL;
		free(it->prev);
		it->prev = NULL;
	}
	free(it->str);
	free(it);
	it = NULL;
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