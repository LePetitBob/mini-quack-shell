/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:02:59 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/04 04:11:21 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	convert_spaces(char *(**arr), char space)
{
	int		row;
	int		col;

	row = 0;
	while ((*arr)[row])
	{
		col = 0;
		if ((*arr)[row] && ft_strsrch((*arr)[row], '\"') > -1)
			++row;
		else
		{
			while ((*arr)[row][col] != '\0')
			{
				if ((*arr)[row][col] == space)
					(*arr)[row][col] *= -1;
				++col;
			}
			++row;
		}
	}
	return ;
}

void	del_quotes(char *(*str))
{
	char	*cpy;
	char	quote;
	int		i;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
		{
			quote = (*str)[i];
			if ((*str)[i + 1] == quote)
			{
				cpy = ft_del_one(*str, i);
				free(*str);
				*str = ft_del_one(cpy, i);
				free(cpy);
			}
			else
				copy_str_without_quotes(str, &i, quote);
		}
		else
			++i;
	}
}

void	copy_str_without_quotes(char *(*str), int *i, char quote)
{
	char	*prefix;
	char	*sufix;
	char	*cpy;
	char	*tmp;
	int		diff;

	diff = (*i) + 1;
	prefix = ft_substr(*str, 0, *i);
	while ((*str)[diff] != '\0' && (*str)[diff] != quote)
		++diff;
	cpy = ft_substr(*str, (*i) + 1, diff - (*i) - 1);
	tmp = ft_strjoin(prefix, cpy);
	if ((*str)[diff] == '\0')
		sufix = ft_substr(*str, diff, ft_strlen(*str) - (diff + 1));
	else
		sufix = ft_substr(*str, diff + 1, ft_strlen(*str) - (diff + 1));
	free(*str);
	*str = ft_strjoin(tmp, sufix);
	free(prefix);
	free(cpy);
	free(tmp);
	free(sufix);
	*i = diff - 1;
}
