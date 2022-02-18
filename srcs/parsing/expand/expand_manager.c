/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:03:12 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/18 15:59:06 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	expand_caller(t_token *tokens, t_env *env)
{
	t_token	*it;

	it = tokens;
	while (it)
	{
		if (it->type == WORD && (ft_strsrch(it->str, '\'') != -1
			|| ft_strsrch(it->str, '\"') != -1
			|| ft_strsrch(it->str, '$') != -1))
			expand_manager(&it, env);
		if (!it)
			return ;
		it = it->next;
	}
	ft_putstr("\n_____expand:\n");
	print_tokens(tokens);
	printf("\n");
	command_manager(tokens, env);
}

void	expand_manager(t_token **it, t_env *env)
{
	char	**arr;
	int		i;

	i = 0;
	printf("\n___line:\n[it]->[%s]\n\n", (*it)->str);
	arr = expand_split_manager((*it)->str);
	convert_spaces(&arr, ' ');
	printf("___split_\'_\"_$_(converted whitespaces):\n");
	ft_print_tab(arr);
	printf("\n\n");
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
		printf("___token_is_now_NULL_because_wrong_$\n");
		return ;
	}
	printf("___expanded_vars:\n");
	ft_print_tab(arr);
	printf("\n");
	join_vars(&arr);
	printf("___joined_everything:\n");
	ft_print_tab(arr);
	printf("\n");
	expand_split_whitespaces(&arr);
	printf("___splited_whitespaces:\n");
	ft_print_tab(arr);
	printf("\n");
	i = 0;
	while (arr[i])
	{
		if (ft_strsrch(arr[i], '\'') != -1 || ft_strsrch(arr[i], '\"') != -1)
			del_quotes(&arr[i]);
		++i;
	}
	printf("___del_quotes:\n");
	ft_print_tab(arr);
	printf("\n");
	convert_spaces(&arr, ' ' * -1);
	printf("___conv_?_to_whitespaces:\n");
	ft_print_tab(arr);
	printf("\n");
	tokenize_expanded_vars(arr, it);
	ft_freetab(arr);
	printf("___tokenized:\n");
	print_tokens(*it);
}
