/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:07:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/18 17:31:12 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	expand_var(char **str, t_env *env)
{
	char	*cpy;
	char	*var;
	char	*value;
	int		i;

	cpy = NULL;
	if ((*str)[0] == '\'')
		return ;
	i = ft_strsrch(*str, '$');
	if (i > 0)
		cpy = ft_strndup((*str), i);
	++i;
	if ((*str)[i] == '?')
	{
		value = ft_itoa(g_exit_status);
		if (cpy)
		{
			value = ft_strjoin(cpy, value);
			free(cpy);
		}
		cpy = ft_substr(*str, i + 1, ft_strlen(*str) - i + 1);
		free(*str);
		*str = ft_strjoin(value, cpy);
		return ;
	}
	if ((*str)[i] == '0')
	{
		value = ft_strdup("mini_quack_shell");
		if (cpy)
		{
			value = ft_strjoin(cpy, value);
			free(cpy);
		}
		cpy = ft_substr(*str, i + 1, ft_strlen(*str) - i + 1);
		free(*str);
		*str = ft_strjoin(value, cpy);
		return ;
	}
	var = ft_strdup(*str);
	ft_bzero(var, ft_strlen(var));
	while ((*str)[i] != '\0' && (ft_isalnum((*str)[i]) == 1
		|| (*str)[i] == '_'))
	{
		var[ft_strlen(var)] = (*str)[i];
		++i;
	}
	value = get_env_name(env, var);
	if ((*str)[0] != '$')
	{
		value = ft_strjoin(cpy, value);
		free(cpy);
	}
	if ((*str)[i] != '\0')
	{
		cpy = ft_substr(*str, i, ft_strlen(*str) - i);
		value = ft_strjoin(value, cpy);
		free(cpy);
	}
	free(*str);
	*str = ft_strdup(value);
	free(var);
	free(value);
}
