/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:18:30 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/14 18:04:52 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	tokenize_expanded_vars(char **arr, t_token **parent)
{
	t_token	*new_token;
	t_token	*it;

	if (!arr && (*parent)->type != FD)
		return (relink_parent_to_himself(parent));
	new_token = make_new_tokens(arr);
	if (!new_token)
		return (ft_free_tab(arr));
	it = get_last_token(new_token);
	new_token->type = (*parent)->type;
	if ((*parent)->prev)
	{
		new_token->prev = (*parent)->prev;
		(*parent)->prev->next = new_token;
	}
	free((*parent)->str);
	(*parent)->str = ft_strdup(it->str);
	(*parent)->type = it->type;
	if (it->prev)
	{
		(*parent)->prev = it->prev;
		it->prev->next = (*parent);
	}
	free(it->str);
	free(it);
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
	if (!arr || !new_token)
		return (new_token);
	new_token->str = ft_strdup(arr[0]);
	it = new_token;
	i = 1;
	while (arr[i])
	{
		it->next = ft_create_empty_token();
		if (!it->next)
			return (free_token(new_token));
		it->next->str = ft_strdup(arr[i]);
		it->next->type = WORD;
		it->next->prev = it;
		it = it->next;
		++i;
	}
	return (new_token);
}
