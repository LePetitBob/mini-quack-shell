/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_whitespaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:49:46 by user42            #+#    #+#             */
/*   Updated: 2022/02/25 05:05:13 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	split_whitespaces(char *str, char *(**args))
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strnew(ft_strlen(str));
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			if (split_skip_quotes(args, str, &i, &tmp) == EXIT_FAILURE)
				return ;
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

int	split_skip_quotes(char *(**args), char *str, int *index, char **tmp)
{
	char	quote;

	quote = str[*index];
	(*tmp)[ft_strlen(*tmp)] = str[*index];
	++*index;
	while (str[*index] != '\0' && str[*index] != quote)
	{
		(*tmp)[ft_strlen(*tmp)] = str[*index];
		++*index;
	}
	if (ret_error_quotes(str, *index, *tmp, args, quote) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ret_error_quotes(char *str, int i, char *tmp, char *(**args), char quote)
{
	if (str[i] != quote)
	{
		free(tmp);
		ft_freetab(*args);
		if (quote == '\'')
			error_manager(ERNO_S_QUOTE, NULL);
		else
			error_manager(ERNO_D_QUOTE, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
