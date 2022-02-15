/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:02:59 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/15 18:07:27 by amarini-         ###   ########.fr       */
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
	char	**splited;
	char	**tmp;
	char	*joined;

	splited = ft_split(*str, '\'');
	while (splited[1])
	{
		joined = ft_strjoin(splited[0], splited[1]);
		tmp = ft_erase(splited, 0, 2);
		ft_freetab(splited);
		splited = ft_insert_tab(tmp, joined, 0);
		free(joined);
	}
	free(*str);
	*str = ft_strdup(splited[0]);
	ft_freetab(splited);
	splited = ft_split(*str, '\"');
	while (splited[1])
	{
		joined = ft_strjoin(splited[0], splited[1]);
		tmp = ft_erase(splited, 0, 2);
		ft_freetab(splited);
		splited = ft_insert_tab(tmp, joined, 0);
		free(joined);
	}
	free(*str);
	*str = ft_strdup(splited[0]);
	ft_freetab(splited);
}