/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:45:53 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/14 18:06:23 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

char	**expand_split_manager(char *str)
{
	char	**res;
	char	**tmp;
	char	*cpy;
	int		i;

	i = 0;
	cpy = ft_strdup(str);
	ft_bzero(cpy, ft_strlen(str));
	res = NULL;
	res = split_expand_prefix(str, &i);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			tmp = ft_add_tab(res, cpy);
			ft_bzero(cpy, ft_strlen(cpy));
			res = ft_tabdup(tmp);
			ft_freetab(tmp);
			split_quotes_expand(&res, str, &i);
		}
		else if (str[i] == '$')
		{
			tmp = ft_add_tab(res, cpy);
			ft_bzero(cpy, ft_strlen(cpy));
			res = ft_tabdup(tmp);
			ft_freetab(tmp);
			split_dollar_expand(&res, str, &i);
		}
		else
			cpy[ft_strlen(cpy)] = str[i];
		++i;
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
		++i;
	}
	if (cpy[0] != '\0')
		res = ft_add_tab(res, cpy);
	free(cpy);
	return (res);
}

void	split_quotes_expand(char *(**arr), char *str, int *index)
{
	char	**tmp;
	char	*cpy;
	char	quote;
	int		i;

	i = 0;
	quote = str[*index];
	cpy = ft_strdup(str);
	ft_bzero(cpy, ft_strlen(cpy));
	while (str[*index + i] != '\0' && str[*index + i] != quote)
	{
		cpy[i] = str[*index + i];
		++i;
	}
	*index += i;
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

	cpy = ft_strdup(str);
	ft_bzero(cpy, ft_strlen(str));
	cpy[0] = str[*index];
	i = 2;
	++*index;
	if (ft_isalpha(str[*index]) == 0 && str[*index] != '_')
		return ;
	while (str[*index + i] != '\0' && ft_isalnum(str[*index + i]) == 1)
	{
		cpy[i] = str[*index + i];
		++i;
	}
	*index += i;
	tmp = ft_add_tab(*arr, cpy);
	free(cpy);
	*arr = ft_tabdup(tmp);
	ft_freetab(tmp);
}
