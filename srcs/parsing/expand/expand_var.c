/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:07:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/15 14:39:14 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	expand_var(char **str, t_env *env)
{
	char	*cpy;
	char	*var;
	char	*value;
	int		i;

	if ((*str)[0] == '\'')
		return ;
	i = ft_strsrch(*str, '$');
	if (i > 0)
		cpy = ft_strndup((*str), i);
	++i;
	var = ft_strdup(*str);
	ft_bzero(var, ft_strlen(var));
	while ((*str)[i] != '\0' && (ft_isalnum((*str)[i]) == 1
		|| (*str)[i] == '_'))
	{
		var[ft_strlen(var)] = (*str)[i];
		++i;
	}
	value = get_env_name(env, var);
	if (!value)
		value = ft_strdup(var);
	if ((*str)[0] != '$')
	{
		value = ft_strjoin(cpy, value);
		free(cpy);
	}
	if ((*str)[i] != '\0')
	{
		cpy = ft_strdup(*str);
		ft_bzero(cpy, ft_strlen(cpy));
		while ((*str)[i] != '\0')
		{
			cpy[ft_strlen(cpy)] = (*str)[i];
			++i;
		}
		value = ft_strjoin(value, cpy);
		free(cpy);
	}
	free(*str);
	*str = ft_strdup(value);
	free(var);
	free(value);
}
