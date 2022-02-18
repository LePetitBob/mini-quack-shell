/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:18:30 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/18 15:52:46 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	tokenize_expanded_vars(char **arr, t_token **parent)
{
	t_token	*new_token;
	t_token	*it;
	int		i;

	if (!arr)
	{
		if ((*parent)->prev)
		{
			if ((*parent)->next)
			{
				(*parent)->prev->next = (*parent)->next;
				(*parent)->next->prev = (*parent)->prev;
			}
			else
				(*parent)->prev->next = NULL;
		}
		else if ((*parent)->next)
		{
			(*parent) = (*parent)->next;
			free((*parent)->prev->str);
			free((*parent)->prev);
			(*parent)->prev = NULL;
		}
		else
		{
			free(*parent);
			*parent = NULL;
		}
		return ;
	}
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
