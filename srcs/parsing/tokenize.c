/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:56:25 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/11 17:55:58 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	tokenize_manager(char *(**args))
{
	t_token	*tokens;
	t_token	*it;
	int		i;

	i = 0;
	tokens = ft_create_empty_token();
	tokens->str = ft_strdup((*args)[i]);
	tokens->type = get_arg_type((*args)[0], NO_TYPE);
	++i;
	it = tokens;
	while ((*args)[i])
	{
		it->next = ft_create_empty_token();
		it->next->str = ft_strdup((*args)[i]);
		it->next->type = get_arg_type((*args)[i], it->type);
		it->next->prev = it;
		it = it->next;
		++i;
	}
	print_tokens(tokens);
	ft_freetab(*args);
	//call next function
	expand_manager(tokens);
}

int	get_arg_type(char *arg, int prev_type)
{
	int	type;

	if (ft_strcmp(arg, "|") == 0)
		type = PIPE;
	else if (ft_strcmp(arg, "<") == 0)
		type = RIN;
	else if (ft_strcmp(arg, "<<") == 0)
		type = HERE_DOC;
	else if (ft_strcmp(arg, ">") == 0)
		type = ROUT;
	else if (ft_strcmp(arg, ">>") == 0)
		type = DROUT;
	else if (prev_type == RIN || prev_type == ROUT || prev_type == DROUT)
		type = FD;
	else if (prev_type == HERE_DOC)
		type = LIMITER;
	else
		type = WORD;
	return (type);
}
