/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:47:00 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/22 11:55:18 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*iterator;

	iterator = tokens;
	while (iterator)
	{
		ft_putstr("[");
		if (iterator->type == NO_TYPE)
			ft_putstr("NO_TYPE");
		else if (iterator->type == WORD)
			ft_putstr("WORD");
		else if (iterator->type == PIPE)
			ft_putstr("PIPE");
		else if (iterator->type == FD)
			ft_putstr("FD");
		else if (iterator->type == LIMITER)
			ft_putstr("LIMITER");
		else if (iterator->type == RIN)
			ft_putstr("RIN");
		else if (iterator->type == ROUT)
			ft_putstr("ROUT");
		else if (iterator->type == DROUT)
			ft_putstr("DROUT");
		else if (iterator->type == HERE_DOC)
			ft_putstr("HERE_DOC");
		ft_putstr("]");
		ft_putstr("[");
		ft_putstr(iterator->str);
		ft_putstr("]\n");
		iterator = iterator->next;
	}
}

void	print_cmds(t_cmd *cmds)
{
	t_cmd	*iterator;

	iterator = cmds;
	while (iterator)
	{
		ft_putstr("cmds:\n{");
		print_tokens(iterator->arg);
		ft_putstr("}\n");
		ft_putstr("redir:\n{");
		print_tokens(iterator->redir);
		ft_putstr("}\n");
		iterator = iterator->next;
	}
	if (iterator == NULL)
		ft_putstr("{NULL}\n");
}
