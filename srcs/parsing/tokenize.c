/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:56:25 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/22 17:30:57 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	tokenize_manager(char *(**args), t_env *env)
{
	t_token	*tokens;
	t_token	*it;
	int		i;

	tokens = ft_create_empty_token();
	tokens->str = ft_strdup((*args)[0]);
	tokens->type = get_arg_type((*args)[0], NO_TYPE);
	i = 1;
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
	ft_freetab(*args);
	if (check_tokens_type(tokens) == EXIT_FAILURE)
	{
		free_token(tokens);
		return ;
	}
	expand_caller(tokens, env);
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

int	check_tokens_type(t_token *tokens)
{
	t_token	*it;

	it = tokens;
	while (it)
	{
		if ((it->type == RIN || it->type == ROUT || it->type == DROUT
				|| it->type == HERE_DOC) && (!it->next || it->next->type == RIN
				|| it->next->type == ROUT || it->next->type == DROUT
				|| it->next->type == HERE_DOC))
		{
			get_error_redir(it->next);
			return (EXIT_FAILURE);
		}
		it = it->next;
	}
	return (EXIT_SUCCESS);
}
