/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 05:53:26 by amarini-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/04 04:31:55 by amarini-         ###   ########.fr       */
=======
/*   Updated: 2022/03/04 06:54:35 by vduriez          ###   ########.fr       */
>>>>>>> debugvinc
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

int	check_quote_expand(char **str)
{
	int		i;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '$')
			return (i);
		if ((*str)[i] == '\'')
		{
			++i;
			while ((*str)[i] != '\0' && (*str)[i] != '\'')
				++i;
		}
		else
			++i;
	}
	return (-1);
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
			value = ft_strdup("mini_quack_shell");
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

char	*get_exp_var_name(char *str, int *index)
{
	char	*var;
	int		i;

	i = 0;
	var = ft_strnew(ft_strlen(str));
	while (str[*index] != '\0' && (ft_isalnum(str[*index]) == 1
			|| str[*index] == '_'))
	{
		var[i] = str[*index];
		++i;
		++(*index);
	}
	if (str[*index] == '$')
		var[i] = str[*index];
	return (var);
}

void	join_pre_sufix_expanded_var(char **str, int i, char **value, char *cpy)
{
	char	*tmp;

	if ((*str)[0] != '$')
	{
		tmp = ft_strjoin(cpy, *value);
		free(*value);
		free(cpy);
		*value = ft_strdup(tmp);
		free(tmp);
	}
	if ((*str)[i] != '\0')
	{
		tmp = ft_substr(*str, i, ft_strlen(*str) - i);
		cpy = ft_strjoin(*value, tmp);
		free(tmp);
		free(*value);
		*value = ft_strdup(cpy);
		free(cpy);
	}
}
