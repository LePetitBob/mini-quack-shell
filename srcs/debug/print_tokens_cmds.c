/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:47:00 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/24 05:41:44 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*iterator;

	iterator = tokens;
	while (iterator)
	{
		dprintf(2, "[");
		if (iterator->type == NO_TYPE)
			dprintf(2, "NO_TYPE");
		else if (iterator->type == WORD)
			dprintf(2, "WORD");
		else if (iterator->type == PIPE)
			dprintf(2, "PIPE");
		else if (iterator->type == FD)
			dprintf(2, "FD");
		else if (iterator->type == LIMITER)
			dprintf(2, "LIMITER");
		else if (iterator->type == RIN)
			dprintf(2, "RIN");
		else if (iterator->type == ROUT)
			dprintf(2, "ROUT");
		else if (iterator->type == DROUT)
			dprintf(2, "DROUT");
		else if (iterator->type == HERE_DOC)
			dprintf(2, "HERE_DOC");
		dprintf(2, "]");
		dprintf(2,"[%s]", iterator->str);
		iterator = iterator->next;
	}
	if (!iterator)
		dprintf(2, "[NULL]");
}

void	print_cmds(t_cmd *cmds)
{
	t_cmd	*iterator;

	iterator = cmds;
	dprintf(2, "\n__________START");
	while (iterator)
	{
		dprintf(2, "cmds:\n{");
		print_tokens(iterator->arg);
		dprintf(2, "}\n");
		dprintf(2, "redir:\n{");
		print_tokens(iterator->redir);
		dprintf(2, "}\n");
		iterator = iterator->next;
	}
	if (iterator == NULL)
		dprintf(2, "{NULL}\n");
	dprintf(2, "__________END\n");
}
