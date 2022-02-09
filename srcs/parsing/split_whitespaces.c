/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_whitespaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:49:46 by user42            #+#    #+#             */
/*   Updated: 2022/02/09 19:46:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

char	**split_whitespaces(char *str)
{
	char	**res;
	char	*tmp;
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = NULL;
	tmp = ft_strdup(str);
	ft_bzero(tmp, ft_strlen(str));
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			++i;
			while (str[i] != quote)
			{
				tmp[j] = str[i];
				++i;
				++j;
			}
		}
		if (str[i] == ' ')
		{
			res = ft_addtab(res, tmp);
			j = 0;
			ft_bzero(tmp);
		}
		else
		{
			tmp[j] = str[i];
			++j;
		}
		++i;
	}
	if (tmp[j] != '\0')
		res = ft_add_tab(res, tmp);
	free(tmp);
	return (res);
}
