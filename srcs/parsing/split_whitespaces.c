/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_whitespaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:49:46 by user42            #+#    #+#             */
/*   Updated: 2022/02/19 00:27:37 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	split_whitespaces(char *str, char *(**args))
{
	char	*tmp;
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_strdup(str);
	ft_bzero(tmp, ft_strlen(str));
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			tmp[j] = str[i];
			quote = str[i];
			++i;
			++j;
			while (str[i] != '\0' && str[i] != quote)
			{
				tmp[j] = str[i];
				++i;
				++j;
			}
			if (str[i] != quote)
			{
				free(tmp);
				free(str);
				if (*args)
					ft_freetab(*args);
				*args = NULL;
				error_manager(ERNO_QUOTE);
				return ;
			}
		}
		if (str[i] == ' ')
		{
			(*args) = ft_add_tab((*args), tmp);
			j = 0;
			ft_bzero(tmp, ft_strlen(str));
		}
		else
		{
			tmp[j] = str[i];
			++j;
		}
		++i;
	}
	if (tmp[0] != '\0')
		(*args) = ft_add_tab((*args), tmp);
	free(tmp);
}

void	expand_split_whitespaces(char *(**arr))
{
	char	**tmp;
	char	*cpy;
	char	quote;
	int		i;

	i = 0;
	cpy = ft_strdup((*arr)[0]);
	ft_bzero(cpy, ft_strlen(cpy));
	while ((*arr)[0][i] != '\0')
	{
		if ((*arr)[0][i] == ' ' && cpy[0] != '\0')
		{
			tmp = ft_add_tab((*arr), cpy);
			ft_bzero(cpy, ft_strlen(cpy));
			*arr = ft_tabdup(tmp);
			ft_freetab(tmp);
		}
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
		if((*arr)[0][i] != ' ')
			cpy[ft_strlen(cpy)] = (*arr)[0][i];
		++i;
	}
	if (cpy[0] != '\0')
	{
		tmp = ft_add_tab((*arr), cpy);
			ft_bzero(cpy, ft_strlen(cpy));
			*arr = ft_tabdup(tmp);
			ft_freetab(tmp);
	}
	tmp = ft_erase(*arr, 0, 1);
	ft_freetab(*arr);
	*arr = ft_tabdup(tmp);
	ft_freetab(tmp);
	free(cpy);
}
