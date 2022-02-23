/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split_whitespace.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 04:09:47 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/23 04:22:03 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	expand_split_whitespaces(char *(**arr))
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = ft_strnew(ft_strlen((*arr)[0]));
	while ((*arr)[0][i] != '\0')
	{
		if ((*arr)[0][i] == ' ' && cpy[0] != '\0')
			add_non_whitespace(arr, cpy);
		if ((*arr)[0][i] == '\'' || (*arr)[0][i] == '\"')
			expand_skip_quotes(arr, &cpy, &i);
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

void	expand_skip_quotes(char *(**arr), char **cpy, int *index)
{
	char	quote;

	(*cpy)[ft_strlen(*cpy)] = (*arr)[0][*index];
	quote = (*arr)[0][*index];
	++*index;
	while ((*arr)[0][*index] != '\0' && (*arr)[0][*index] != quote)
	{
		(*cpy)[ft_strlen(*cpy)] = (*arr)[0][*index];
		++*index;
	}
}
