/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_whitespaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:49:46 by user42            #+#    #+#             */
/*   Updated: 2022/03/11 11:42:01 by amarini-         ###   ########.fr       */
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
		if (check_wsp(str[i]) == IS_WSP)
		{
			if (tmp[0] != '\0')
				(*args) = ft_add_tab((*args), tmp);
			ft_bzero(tmp, ft_strlen(str));
			while (str[i + 1] != '\0' && check_wsp(str[i + 1]) == IS_WSP)
				++i;
		}
		else
			tmp[ft_strlen(tmp)] = str[i];
		++i;
	}
	if (tmp[0] != '\0')
		(*args) = ft_add_tab((*args), tmp);
	free(tmp);
}

int	check_wsp(char c)
{
	if (c != ' ' && c != '\t' && c != '\n' && c != '\v' && c != '\f'
		&& c != '\r')
		return (1);
	return (0);
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
	char	*err;

	if (str[i] != quote)
	{
		free(tmp);
		ft_freetab(*args);
		*args = NULL;
		err = ft_strnew(2);
		err[0] = quote;
		error_manager(ERNO_SYNTAX, err);
		free(err);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
