/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:04:23 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/26 03:02:54 by amarini-         ###   ########.fr       */
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

void	split_dollar_expand(char *(**arr), char *str, int *index)
{
	char	**tmp;
	char	*cpy;

	++(*index);
	if (str[*index] != '\0' && (ft_isalpha(str[*index]) == 0
			&& str[*index] != '_' && str[*index] != '0'
			&& str[*index] != '?' && str[*index] != '$'))
	{
		--(*index);
		return ;
	}
	cpy = ft_strnew(ft_strlen(str));
	cpy[0] = str[(*index) - 1];
	while (str[*index] != '\0' && (ft_isalnum(str[*index]) == 1
			|| str[*index] == '_'))
	{
		cpy[ft_strlen(cpy)] = str[*index];
		++(*index);
	}
	if (str[*index] == '?')
		cpy[ft_strlen(cpy)] = str[*index];
	if (ft_isalnum(str[*index]) == 0 && str[*index] != '_'
		&& str[*index] != '0' && str[*index] != '?')
		--(*index);
	tmp = ft_add_tab(*arr, cpy);
	free(cpy);
	*arr = ft_tabdup(tmp);
	ft_freetab(tmp);
}
