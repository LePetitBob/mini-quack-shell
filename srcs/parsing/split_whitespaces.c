/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_whitespaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:49:46 by user42            #+#    #+#             */
/*   Updated: 2022/02/10 14:50:58 by amarini-         ###   ########.fr       */
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
			while (str[i] != quote)
			{
				tmp[j] = str[i];
				++i;
				++j;
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
