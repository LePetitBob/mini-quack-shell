/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_fd_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 01:56:31 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/23 02:05:13 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	link_fd_redir(t_token **tokens)
{
	t_token	*it;

	it = *tokens;
	while (it->next)
	{
		if ((it->next->type == FD || it->next->type == LIMITER)
			&& (it->type == RIN || it->type == ROUT || it->type == DROUT
				|| it->type == HERE_DOC))
			relink_node_parent(&it, tokens);
		else
			it = it->next;
	}
}

void	relink_node_parent(t_token **it, t_token **head)
{
	t_token	*tmp;

	tmp = *it;
	*it = (*it)->next;
	(*it)->type = tmp->type;
	if (tmp->prev)
	{
		(*it)->prev = tmp->prev;
		tmp->prev->next = *it;
	}
	else
	{
		(*it)->prev = NULL;
		*head = *it;
	}
	free_one_token(tmp);
}
