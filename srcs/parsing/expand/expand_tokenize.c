/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:18:30 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/01 08:58:04 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	tokenize_expanded_vars(char **arr, t_token **parent)
{
	t_token	*new_token;
	t_token	*it;

	if (!arr)
	{
		relink_parent_to_himself(parent);
		return ;
	}
	new_token = make_new_tokens(arr);
	it = get_last_token(new_token);
	if ((*parent)->next)
	{
		it->next = (*parent)->next;
		(*parent)->next->prev = it;
	}
	free((*parent)->str);
	(*parent)->str = ft_strdup(new_token->str);
	if (new_token->next)
	{
		(*parent)->next = new_token->next;
		new_token->next->prev = (*parent);
	}
	free(new_token->str);
	free(new_token);
}

void	relink_parent_to_himself(t_token **parent)
{
	t_token	*tmp;

	tmp = *parent;
	if ((*parent)->prev)
	{
		*parent = (*parent)->prev;
		if (tmp->next)
		{
			(*parent)->next = tmp->next;
			tmp->next->prev = (*parent);
		}
		else
			(*parent)->next = NULL;
	}
	else if ((*parent)->next)
	{
		(*parent) = (*parent)->next;
		(*parent)->prev = NULL;
	}
	else
		return (no_link_parent(parent));
	free(tmp->str);
	free(tmp);
	tmp = NULL;
}

void	no_link_parent(t_token **parent)
{
	free((*parent)->str);
	free(*parent);
	*parent = NULL;
	return ;
}

t_token	*make_new_tokens(char **arr)
{
	t_token	*new_token;
	t_token	*it;
	int		i;

	new_token = ft_create_empty_token();
	new_token->str = ft_strdup(arr[0]);
	it = new_token;
	i = 1;
	while (arr[i])
	{
		it->next = ft_create_empty_token();
		it->next->str = ft_strdup(arr[i]);
		it->next->type = WORD;
		it->next->prev = it;
		it = it->next;
		++i;
	}
	return (new_token);
}
