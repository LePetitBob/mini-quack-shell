/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:07:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/26 04:08:58 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern int	g_exit_status;

void	expand_vars_manager(char *(**arr), t_env *env)
{
	char	**tmp;
	int		i;

	i = 0;
	while (*arr && (*arr)[i])
	{
		if (ft_strsrch((*arr)[i], '$') != -1)
		{
			expand_var(&(*arr)[i], env);
			if (!(*arr)[i] || (*arr)[i][0] == '\0')
			{
				tmp = ft_erase(*arr, i, 1);
				ft_freetab(*arr);
				*arr = ft_tabdup(tmp);
				ft_freetab(tmp);
				--i;
			}
		}
		++i;
	}
}

//!ENV VAR IN HERE_DOC MUST BE EXPANDED !!!!!
//!give this to vincent for here_doc
void	expand_var(char **str, t_env *env)
{
	char	*cpy;
	char	*var;
	char	*value;
	int		i;

	cpy = NULL;
	if ((*str)[0] == '\'' || (*str)[ft_strsrch(*str, '$') + 1] == '\0'
		|| (*str)[ft_strsrch(*str, '$') + 1] == '\"')
		return ;
	i = ft_strsrch(*str, '$') + 1;
	if ((i - 1) > 0)
		cpy = ft_strndup((*str), i - 1);
	if (expand_exeptions(str, i, cpy, value) == EXIT_FAILURE)
		return ;
	var = get_exp_var_name(*str, &i);
	value = get_env_name(env, var);
	join_pre_sufix_expanded_var(str, i, &value, cpy);
	free(*str);
	if (!value)
		*str = ft_strdup("\0");
	else
		*str = ft_strdup(value);
	free(var);
	free(value);
}

int	expand_exeptions(char **str, int i, char *cpy, char *value)
{
	char	*tmp;

	tmp = NULL;
	if ((*str)[i] == '?' || (*str)[i] == '0')
	{
		if ((*str)[i] == '?')
			value = ft_itoa(g_exit_status);
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
