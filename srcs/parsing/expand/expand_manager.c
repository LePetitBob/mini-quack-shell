/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:03:12 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/17 14:16:56 by amarini-         ###   ########.fr       */
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
			expand_manager(it, env);
		it = it->next;
	}
	ft_putstr("\n_____expand:\n");
	print_tokens(tokens);
	printf("\n");
}

void	expand_manager(t_token *it, t_env *env)
{
	char	**arr;
	int		i;

	i = 0;
	// printf("\n___line:\n[it]->[%s]\n\n", it->str);
	arr = expand_split_manager(it->str);
	convert_spaces(&arr, ' ');
	// printf("___split_\'_\"_$_(converted whitespaces):\n");
	// ft_print_tab(arr);
	// printf("\n\n");
	while (arr[i])
	{
		if (ft_strsrch(arr[i], '$') != -1)
			expand_var(&arr[i], env);
		++i;
	}
	// printf("___expanded_vars:\n");
	// ft_print_tab(arr);
	// printf("\n");
	join_vars(&arr);
	// printf("___joined_everything:\n");
	// ft_print_tab(arr);
	// printf("\n");
	expand_split_whitespaces(&arr);
	// printf("___splited_whitespaces:\n");
	// ft_print_tab(arr);
	// printf("\n");
	i = 0;
	while (arr[i])
	{
		if (ft_strsrch(arr[i], '\'') != -1 || ft_strsrch(arr[i], '\"') != -1)
			del_quotes(&arr[i]);
		++i;
	}
	// printf("___del_quotes:\n");
	// ft_print_tab(arr);
	// printf("\n");
	convert_spaces(&arr, ' ' * -1);
	// printf("___conv_?_to_whitespaces:\n");
	// ft_print_tab(arr);
	// printf("\n");
	tokenize_expanded_vars(arr, it);
	// ft_freetab(arr);
	// printf("___tokenized:\n");
	// print_tokens(it);
}
