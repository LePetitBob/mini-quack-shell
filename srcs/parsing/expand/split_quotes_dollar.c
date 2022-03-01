/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:04:23 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/01 22:13:20 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	split_quotes_expand(char *(**arr), char *str, int *index)
{
	char	**tmp;
	char	*cpy;
	char	quote;
	int		i;

	i = 1;
	quote = str[*index];
	cpy = ft_strnew(ft_strlen(str));
	cpy[0] = quote;
	while (str[*index + i] != '\0' && str[*index + i] != quote)
	{
		cpy[i] = str[*index + i];
		++i;
	}
	*index += i;
	cpy[ft_strlen(cpy)] = quote;
	tmp = ft_add_tab(*arr, cpy);
	free(cpy);
	*arr = ft_tabdup(tmp);
	ft_freetab(tmp);
}

void	split_dollar_expand(char *(**arr), char *str, int *i)
{
	char	*cpy;

	++(*i);
	if (str[*i] != '\0' && (ft_isalpha(str[*i]) == 0 && str[*i] != '_'
			&& str[*i] != '0' && str[*i] != '?' && str[*i] != '$'))
	{
		--(*i);
		return ;
	}
	cpy = ft_strnew(ft_strlen(str));
	cpy[0] = str[(*i) - 1];
	while (str[*i] != '\0' && (ft_isalnum(str[*i]) == 1 || str[*i] == '_'))
	{
		cpy[ft_strlen(cpy)] = str[*i];
		++(*i);
	}
	if (str[*i] == '?')
		cpy[ft_strlen(cpy)] = str[*i];
	if (ft_isalnum(str[*i]) == 0 && str[*i] != '_' && str[*i] != '0'
		&& str[*i] != '?')
		--(*i);
	*arr = ft_add_tab(*arr, cpy);
	free(cpy);
}
