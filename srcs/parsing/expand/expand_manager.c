/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:03:12 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/13 20:30:27 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	expand_caller(t_token *tokens, t_env *env)
{
	t_token	*it;

	it = tokens;
	while (it)
	{
		if ((it->type == WORD || it->type == FD || it->type == LIMITER)
			&& (ft_strsrch(it->str, '\'') != -1
				|| ft_strsrch(it->str, '\"') != -1
				|| ft_strsrch(it->str, '$') != -1))
			expand_manager(&it, env);
		if (!it)
			return ;
		it = it->next;
	}
	tokens = get_first_token(tokens);
	command_manager(tokens, env);
}

void	expand_manager(t_token **it, t_env *env)
{
	char	**arr;
	int		i;

	i = 0;
	arr = expand_split_manager((*it)->str);
	if (!arr)
		return (ret_empty_expand(&arr, it));
	convert_all_wsp(&arr, 1);
	if ((*it)->type != LIMITER)
		expand_vars_manager(*it, &arr, env);
	if (!arr)
		return (ret_empty_expand(&arr, it));
	join_vars(&arr);
	expand_split_whitespaces(&arr);
	i = 0;
	while (arr[i])
	{
		if (ft_strsrch(arr[i], '\'') != -1 || ft_strsrch(arr[i], '\"') != -1)
			del_quotes(&arr[i]);
		++i;
	}
	convert_all_wsp(&arr, -1);
	tokenize_expanded_vars(arr, it);
	ft_freetab(arr);
}

void	ret_empty_expand(char *(**arr), t_token **it)
{
	tokenize_expanded_vars(*arr, it);
	ft_freetab(*arr);
	return ;
}
