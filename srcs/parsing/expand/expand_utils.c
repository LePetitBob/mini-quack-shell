/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:02:59 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/17 14:10:12 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	convert_spaces(char *(**arr), char space)
{
	int	row;
	int	col;

	row = 0;
	while ((*arr)[row])
	{
		col = 0;
		while ((*arr)[row][col] != '\0')
		{
			if ((*arr)[row][col] == space)
				(*arr)[row][col] *= -1;
			++col;
		}
		++row;
	}
	return ;
}

void	del_quotes(char *(*str))
{
	char	*prefix;
	char	*sufix;
	char	*cpy;
	char	quote;
	int		i;
	int		diff;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
		{
			quote = (*str)[i];
			diff = i + 1;
			if ((*str)[diff] == quote)
			{
				cpy = ft_del_one(*str, i);
				free(*str);
				*str = ft_del_one(cpy, i);
				free(cpy);
			}
			else
			{
				prefix = ft_substr(*str, 0, i);
				while ((*str)[diff] != '\0' && (*str)[diff] != quote)
					++diff;
				cpy = ft_substr(*str, i + 1, diff - i - 1);
				sufix = ft_strjoin(prefix, cpy);
				free(cpy);
				cpy = ft_strdup(sufix);
				free(sufix);
				if ((*str)[diff] == '\0')
					sufix = ft_substr(*str, diff, ft_strlen(*str) - (diff + 1));
				else
					sufix = ft_substr(*str, diff + 1, ft_strlen(*str) - (diff + 1));
				free(*str);
				*str = ft_strjoin(cpy, sufix);
				free(prefix);
				free(sufix);
				free(cpy);
				i = diff - 1;
			}
			// printf("str-[%s]\n", *str);
		}
		else
			++i;
	}
}