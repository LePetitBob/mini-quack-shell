/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 05:53:26 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/11 12:06:39 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

int	check_quote_expand(char *str)
{
	int		i;
	int		tmp;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (ft_isalnum(str[i + 1]) == 0 && str[i + 1] != '$'
				&& str[i + 1] != '?')
				return (-1);
			return (i);
		}
		if (str[i] == '\'')
		{
			tmp = ++i;
			while (str[tmp] != '\0' && str[tmp] != '\'')
				++tmp;
			if (str[tmp] == '\'')
				i += tmp;
		}
		else
			++i;
	}
	return (-1);
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

void	join_prefix_to_var(char **str, char **value, char *cpy)
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
}

int	check_ambigous(char **str)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	if (!(*str) || (*str)[0] == '\0')
		return (free_ambigous(str));
	while ((*str)[i] != '\0')
	{
		if (check_wsp((*str)[i]) == IS_WSP)
		{
			tmp = i;
			while ((*str)[tmp] != '\0' && check_wsp((*str)[tmp]) == IS_WSP)
				++tmp;
			if (i != 0 && (*str)[tmp] != '\0'
				&& check_wsp((*str)[tmp]) == NOT_WSP)
				return (free_ambigous(str));
			i += tmp;
		}
		++i;
	}
	return (0);
}

int	free_ambigous(char **str)
{
	free(*str);
	*str = NULL;
	return (1);
}
