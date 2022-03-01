/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:54:27 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/01 22:44:12 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	split_manager(char *line, t_env *env)
{
	char	**args;

	if (line[0] == '\0')
	{
		free(line);
		return ;
	}
	args = NULL;
	split_whitespaces(line, &args);
	if (!args)
	{
		free(line);
		return ;
	}
	split_seps(&args);
	if (syntax_errors(ft_tabdup(args)) == EXIT_FAILURE)
	{
		free(line);
		ft_freetab(args);
		return ;
	}
	free(line);
	tokenize_manager(&args, env);
}

int	syntax_errors(char **arr)
{
	char	*err;
	int		i;

	join_vars(&arr);
	i = pipe_error(arr[0]);
	err = ft_strnew(3);
	if (i == -1 || (misc_errors(arr[0], ';') != -1
			&& misc_errors(arr[0], ';') < i))
		i = misc_errors(arr[0], ';');
	if (i == -1 || (misc_errors(arr[0], '&') != -1
			&& misc_errors(arr[0], '&') < i))
		i = misc_errors(arr[0], '&');
	if (i == -1 || (misc_errors(arr[0], '\\') != -1
			&& misc_errors(arr[0], '\\') < i))
		i = misc_errors(arr[0], '\\');
	if (i >= 0)
	{
		err[0] = arr[0][i];
		if (ft_strlen(arr[0]) > 1 && ((i <= ft_strlen(arr[0]) - 1
				&& arr[0][i] == arr[0][i + 1])
				|| (i == ft_strlen(arr[0]) - 1 && arr[0][i] == arr[0][i - 1])))
			err[1] = arr[0][i];
		error_manager(ERNO_SYNTAX, err);
		ft_freetab(arr);
		free(err);
		return (EXIT_FAILURE);
	}
	ft_freetab(arr);
	free(err);
	return (EXIT_SUCCESS);
}

int	misc_errors(char *str, char pb)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == pb)
			return (i);
		++i;
	}
	return (-1);
}

int	pipe_error(char *str)
{
	int	i;

	if (str[0] == '|')
		return (0);
	else if (ft_strlen(str) > 1 && str[ft_strlen(str) - 1] == '|')
		return (ft_strlen(str) - 1);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (i);
		++i;
	}
	return (-1);
}
