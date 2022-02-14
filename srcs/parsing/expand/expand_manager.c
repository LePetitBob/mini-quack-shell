/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:03:12 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/14 18:09:29 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	expand_caller(t_token *tokens, t_env *env)
{
	t_token	*it;

	it = tokens;
	while (it)
	{
		if (ft_strsrch(it->str, '\'') != -1 || ft_strsrch(it->str, '\"') != -1
			|| ft_strsrch(it->str, '$') != -1)
		{
			expand_split_manager
		}
	}
}

void	expand_manager(t_token *it, t_env *env)
{
	char	**arr;

	ft_printf("[it]->[%s]\n", it->str);
	//split $'"
		//convert space into ? for '
	arr = expand_split_manager(it->str);
	ft_print_tab(arr);
	//expand vars
		//del quotes
	//join everything
	//split spaces
	//conv ? to spaces for
	//tokenize
	//join to existing token
}
