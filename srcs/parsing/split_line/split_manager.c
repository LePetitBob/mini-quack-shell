/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:54:27 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/01 07:42:55 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	split_manager(char *line, t_env *env)
{
	char	**args;

	args = NULL;
	split_whitespaces(line, &args);
	// if (!args || syntax_errors(line, ';') == EXIT_FAILURE
	// 	|| syntax_errors(line, '&') == EXIT_FAILURE)
	// {
	// 	free(line);
	// 	return ;
	// }
	split_seps(&args);
	if (!args || pipe_error(args) == EXIT_FAILURE
		|| syntax_errors(line, ';') == EXIT_FAILURE
		|| syntax_errors(line, '&') == EXIT_FAILURE)
	{
		free(line);
		ft_freetab(args);
		return ;
	}
	free(line);
	tokenize_manager(&args, env);
}

int	syntax_errors(char **args)
{
	char	**tmp;
	char	*err;
	int		i;

	tmp = ft_tabdup(args);
	join_vars(&tmp);
	i = pipe_error(tmp[0]);
	if (misc_errors(tmp[0], ';') < i)
		i = misc_errors(tmp[0], ';');
	if (misc_errors(tmp[0], '&') < i)
		i = misc_errors(tmp[0], '&');
	if (i ==)
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
	else if (str[ft_strlen(str) - 1] == '|')
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
