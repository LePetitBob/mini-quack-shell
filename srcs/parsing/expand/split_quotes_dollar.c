/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:04:23 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/22 14:33:01 by amarini-         ###   ########.fr       */
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
	cpy = ft_strdup(str);
	ft_bzero(cpy, ft_strlen(cpy));
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
	int		i;

	i = 1;
	cpy = ft_strdup(str);
	ft_bzero(cpy, ft_strlen(str));
	cpy[0] = str[*index];
	if (str[*index + i] != '\0' && (ft_isalpha(str[*index + i]) == 0
			&& str[*index + i] != '_' && str[*index + i] != '0'
			&& str[*index + i] != '?'))
	{
		++(*index);
		return ;
	}
	while (str[*index + i] != '\0' && (ft_isalnum(str[*index + i]) == 1
			|| str[*index + i] == '_'))
	{
		cpy[i] = str[*index + i];
		++i;
	}
	*index += i;
	if (str[*index] == '?')
		cpy[i] = str[*index];
	if (ft_isalnum(str[*index]) == 0 && str[*index] != '_'
		&& str[*index] != '0' && str[*index] != '?')
		--(*index);
	tmp = ft_add_tab(*arr, cpy);
	free(cpy);
	*arr = ft_tabdup(tmp);
	ft_freetab(tmp);
}
