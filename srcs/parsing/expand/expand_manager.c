/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:03:12 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/22 14:36:54 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	expand_caller(t_token *tokens, t_env *env)
{
	t_token	*it;

	it = tokens;
	while (it)
	{
		if ((it->type == WORD || it->type == LIMITER)
			&& (ft_strsrch(it->str, '\'') != -1
				|| ft_strsrch(it->str, '\"') != -1
				|| ft_strsrch(it->str, '$') != -1))
			expand_manager(&it, env);
		if (!it)
			return ;
		it = it->next;
	}
	// ft_putstr("__________expanded:\n{");
	// print_tokens(tokens);
	// ft_putstr("__________}\n");
	command_manager(tokens, env);
	// ft_putstr("__________done_expand:\n");
}

void	expand_manager(t_token **it, t_env *env)
{
	char	**arr;
	int		i;

	i = 0;
	arr = expand_split_manager((*it)->str);
	convert_spaces(&arr, ' ');
	while (arr && arr[i])
	{
		if (ft_strsrch(arr[i], '$') != -1)
		{
			expand_var(&arr[i], env);
			if (arr[i][0] == '\0')
				arr = ft_erase(arr, i, 1);
		}
		++i;
	}
	if (!arr)
	{
		tokenize_expanded_vars(arr, it);
		return ;
	}
	join_vars(&arr);
	expand_split_whitespaces(&arr);
	i = 0;
	while (arr[i])
	{
		if (ft_strsrch(arr[i], '\'') != -1 || ft_strsrch(arr[i], '\"') != -1)
			del_quotes(&arr[i]);
		++i;
	}
	convert_spaces(&arr, ' ' * -1);
	tokenize_expanded_vars(arr, it);
	ft_freetab(arr);
}
