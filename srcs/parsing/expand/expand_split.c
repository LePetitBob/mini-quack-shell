/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:45:53 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/15 14:05:29 by amarini-         ###   ########.fr       */
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
	// ft_print_tab(res);
	while (str[i])
	{
		// printf("str[i][%c]\n", str[i]);
		if (str[i] == '\'' || str[i] == '\"')
		{
			// printf("in \'|\"\n");
			if (cpy[0] != '\0')
			{
				tmp = ft_add_tab(res, cpy);
				ft_bzero(cpy, ft_strlen(cpy));
				res = ft_tabdup(tmp);
				ft_freetab(tmp);
			}
			split_quotes_expand(&res, str, &i);
			// ft_print_tab(res);
			// printf("\n");
		}
		else if (str[i] == '$')
		{
			// printf("in $\n");
			if (cpy[0] != '\0')
			{
				tmp = ft_add_tab(res, cpy);
				ft_bzero(cpy, ft_strlen(cpy));
				res = ft_tabdup(tmp);
				ft_freetab(tmp);
			}
			split_dollar_expand(&res, str, &i);
			// ft_print_tab(res);
			// printf("\n");
		}
		else
			cpy[ft_strlen(cpy)] = str[i];
		++i;
	}
	if (cpy[0] != '\0')
	{
		tmp = ft_add_tab(res, cpy);
		res = ft_tabdup(tmp);
		ft_freetab(tmp);
	}
	free(cpy);
	return (res);
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
