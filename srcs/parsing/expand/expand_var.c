/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:07:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/03 05:17:12 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

void	expand_vars_manager(char *(**arr), t_env *env)
{
	char	**tmp;
	int		i;

	i = 0;
	while (*arr && (*arr)[i])
	{
		if (ft_strsrch((*arr)[i], '$') != -1)
		{
			expand_var(&(*arr)[i], env, 0);
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

void	expand_var(char **str, t_env *env, int hd)
{
	char	*cpy;
	char	*var;
	char	*value;
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
