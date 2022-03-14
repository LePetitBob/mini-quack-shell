/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:07:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/14 12:47:15 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

void	expand_vars_manager(t_token *it, char *(**arr), t_env *env)
{
	char	*cpy;
	int		i;

	i = 0;
	while (*arr && (*arr)[i])
	{
		if (ft_strsrch((*arr)[i], '$') != -1)
		{
			cpy = ft_strdup((*arr)[i]);
			expand_var(&cpy, env, 0);
			if (it->type == LIMITER && (!cpy || cpy[0] == '\0'))
				free(cpy);
			else
			{
				if (it->type == FD && check_ambigous(&cpy) == 1)
					send_error_msg(it->str, ERNO_AMBIG_REDIR, 1);
				free((*arr)[i]);
				(*arr)[i] = ft_strdup(cpy);
				free(cpy);
			}
			if (!(*arr)[i] || (*arr)[i][0] == '\0')
				delete_null_var(arr, &i);
		}
		++i;
	}
}

void	expand_var(char **str, t_env *env, int hd)
{
	char	*cpy;
	char	*value;
	char	*var;
	int		i;

	cpy = NULL;
	if (hd == 1)
		i = ft_strsrch(*str, '$');
	else
		i = check_quote_expand(*str);
	if (i == -1 || (i != -1 && ((*str)[i + 1] == '\0'
			|| (*str)[i + 1] == '\"')))
		return ;
	++i;
	if ((i - 1) > 0)
		cpy = ft_strndup((*str), i - 1);
	if (expand_exeptions(str, i, cpy, NULL) == EXIT_FAILURE)
		return ;
	var = get_exp_var_name(*str, &i);
	value = get_env_name(env, var);
	free(var);
	if (hd == 0 && (*str)[i] != '\0')
		value = check_sufix_expand(env, str, value, i);
	join_prefix_to_var(str, &value, cpy);
	get_str(value, str);
}

char	*check_sufix_expand(t_env *env, char **str, char *value, int i)
{
	char	*tmp;
	char	*cpy;

	tmp = ft_substr(*str, i, ft_strlen(*str) - i);
	if (check_quote_expand(tmp) != -1)
		expand_var(&tmp, env, 0);
	cpy = ft_strjoin(value, tmp);
	free(value);
	free(tmp);
	return (cpy);
}

void	get_str(char *value, char **str)
{
	free(*str);
	if (!value)
		*str = ft_strdup("\0");
	else
		*str = ft_strdup(value);
	free(value);
}

void	delete_null_var(char *(**arr), int *index)
{
	char	**tmp;

	tmp = ft_erase(*arr, *index, 1);
	ft_freetab(*arr);
	*arr = ft_tabdup(tmp);
	ft_freetab(tmp);
	--(*index);
}
