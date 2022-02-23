/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split_seps.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:45:53 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/23 07:09:29 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

char	**expand_split_manager(char *str)
{
	char	**res;
	char	*cpy;
	int		i;

	i = 0;
	cpy = ft_strnew(ft_strlen(str));
	res = split_expand_prefix(str, &i);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == '$')
			add_splited_to_args(&res, cpy);
		if (str[i] == '\'' || str[i] == '\"')
			split_quotes_expand(&res, str, &i);
		else if (str[i] == '$')
			split_dollar_expand(&res, str, &i);
		else
			cpy[ft_strlen(cpy)] = str[i];
		++i;
	}
	add_splited_to_args(&res, cpy);
	free(cpy);
	return (res);
}

void	add_splited_to_args(char *(**args), char *str)
{
	if (str[0] != '\0')
	{
		*args = ft_add_tab(*args, str);
		ft_bzero(str, ft_strlen(str));
	}
}

char	**split_expand_prefix(char *str, int *i)
{
	char	**res;
	char	*cpy;

	res = NULL;
	cpy = ft_strdup(str);
	ft_bzero(cpy, ft_strlen(str));
	while (str[*i] != '\0' && str[*i] != '\'' && str[*i] != '\"'
		&& str[*i] != '$')
	{
		cpy[*i] = str[*i];
		++(*i);
	}
	if (cpy[0] != '\0')
		res = ft_add_tab(res, cpy);
	free(cpy);
	return (res);
}
