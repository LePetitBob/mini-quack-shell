/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_whitespaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:49:46 by user42            #+#    #+#             */
/*   Updated: 2022/02/19 06:33:29 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	split_whitespaces(char *str, char *(**args))
{
	char	*tmp;
	char	quote;
	int		i;

	i = 0;
	tmp = ft_strnew(ft_strlen(str));
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			tmp[ft_strlen(tmp)] = str[i];
			quote = str[i];
			++i;
			while (str[i] != '\0' && str[i] != quote)
			{
				tmp[ft_strlen(tmp)] = str[i];
				++i;
			}
			if (str[i] != quote)
			{
				free(tmp);
				free(str);
				if (*args)
					ft_freetab(*args);
				*args = NULL;
				if (quote == '\'')
					error_manager(ERNO_S_QUOTE);
				else
					error_manager(ERNO_D_QUOTE);
				return ;
			}
		}
		if (str[i] == ' ')
		{
			(*args) = ft_add_tab((*args), tmp);
			ft_bzero(tmp, ft_strlen(str));
		}
		else
			tmp[ft_strlen(tmp)] = str[i];
		++i;
	}
	if (tmp[0] != '\0')
		(*args) = ft_add_tab((*args), tmp);
	free(tmp);
}

void	expand_split_whitespaces(char *(**arr))
{
	char	*cpy;
	char	quote;
	int		i;

	i = 0;
	cpy = ft_strnew(ft_strlen((*arr)[0]));
	while ((*arr)[0][i] != '\0')
	{
		if ((*arr)[0][i] == ' ' && cpy[0] != '\0')
			add_non_whitespace(arr, cpy);
		if ((*arr)[0][i] == '\'' || (*arr)[0][i] == '\"')
		{
			cpy[ft_strlen(cpy)] = (*arr)[0][i];
			quote = (*arr)[0][i];
			++i;
			while ((*arr)[0][i] != '\0' && (*arr)[0][i] != quote)
			{
				cpy[ft_strlen(cpy)] = (*arr)[0][i];
				++i;
			}
		}
		if ((*arr)[0][i] != ' ')
			cpy[ft_strlen(cpy)] = (*arr)[0][i];
		++i;
	}
	if (cpy[0] != '\0')
		add_non_whitespace(arr, cpy);
	add_non_whitespace(arr, NULL);
	free(cpy);
}

void	add_non_whitespace(char *(**arr), char *cpy)
{
	char	**tmp;

	if (!cpy)
		tmp = ft_erase(*arr, 0, 1);
	else
	{
		tmp = ft_add_tab(*arr, cpy);
		ft_bzero(cpy, ft_strlen(cpy));
	}
	*arr = ft_tabdup(tmp);
	ft_freetab(tmp);
}
