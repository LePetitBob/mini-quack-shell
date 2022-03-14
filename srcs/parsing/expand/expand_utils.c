/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:02:59 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/14 16:02:00 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	del_quotes(char *(*str))
{
	char	*cpy;
	char	quote;
	int		i;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i + 1] != '\0' && ((*str)[i] == '\'' || (*str)[i] == '\"'))
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
	if ((*str)[diff] == '\0')
		return ;
	prefix = ft_substr(*str, 0, *i);
	while ((*str)[diff] != '\0' && (*str)[diff] != quote)
		++diff;
	if ((*str)[diff] == '\0')
		return (exit_str_without_quotes(prefix, diff, i));
	cpy = ft_substr(*str, (*i) + 1, diff - (*i) - 1);
	tmp = ft_strjoin(prefix, cpy);
	sufix = ft_substr(*str, diff + 1, ft_strlen(*str) - (diff + 1));
	free(*str);
	*str = ft_strjoin(tmp, sufix);
	free(cpy);
	free(tmp);
	free(sufix);
	exit_str_without_quotes(prefix, diff, i);
}

void	exit_str_without_quotes(char *prefix, int diff, int *i)
{
	free(prefix);
	*i = diff - 1;
}

int	expand_exeptions(char **str, int i, char *cpy, char *value)
{
	char	*tmp;

	tmp = NULL;
	if ((*str)[i] == '?' || (*str)[i] == '0')
	{
		if ((*str)[i] == '?')
			value = ft_itoa(g_status.exit_status);
		else if ((*str)[i] == '0')
			value = ft_strdup("minishell");
		if (cpy)
		{
			tmp = ft_strjoin(cpy, value);
			free(cpy);
			free(value);
			cpy = ft_strdup(tmp);
		}
		if ((*str)[i + 1] != '\0')
			value = ft_substr(*str, i + 1, ft_strlen(*str) - i + 1);
		free(*str);
		*str = ft_strjoin(value, cpy);
		free(tmp);
		free(value);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
