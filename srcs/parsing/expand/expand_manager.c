/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:03:12 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/11 19:38:09 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	expand_manager(t_token *tokens, t_env env)
{
	t_token	*it;
	int		i;

	printf("started Expand\n");
	it = tokens;
	while (it)
	{
		printf("it->str-[%s]\n", it->str);
		i = 0;
		if (it->type == WORD)
			while (it->str[i] != '\0')
			{
				if (it->str[i] == '\'' || it->str[i] == '\"'
					|| it->str[i] == '$')
				{
					printf("gonna expand\n");
					expand_str(it, i);
					break ;
				}
				++i;
			}
		it = it->next;
	}
	printf("finished Expand\n");
}

void	expand_str(t_token *it, int index, t_env env)
{
	char	**ret;
	char	*tmp;
	int		i;

	ret = NULL;
	i = 0;
	if (index > 0)
	{
		tmp = ft_strndup(it->str, index);
		ret = ft_add_tab(ret, tmp);
		free(tmp);
		tmp = (char *)malloc((ft_strlen(it->str) - index + 1) * sizeof(char));
		if (!tmp)
			return ;
		tmp[ft_strlen(it->str) - index] = '\0';
		while (i < ft_strlen(it->str) - index)
		{
			tmp[i] = it->str[index + i];
			++i;
		}
		free(it->str);
		it->str = ft_strdup(tmp);
		free(tmp);
	}
	//split str into -> ' " $
	split_quotes_dollar(it->str, &ret);
	ft_print_tab(ret);
	//look at index
		//if '
			//split ' with '
		//if "
			//split " with "
		//if $
			//split $ until non alnum char || _

		//for ' -> del quotes | turn spaces into *-1
		//for " -> del quotes | get env var $
		//for $ -> get env var $
}
