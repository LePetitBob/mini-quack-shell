/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:43:19 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/06 15:19:18 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

char	*get_env_name(t_env *env, char *name)
{
	t_env_var	*tmp;

	tmp = env->first;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_env_var(t_env *env, char **var, int to_print)
{
	if (existing_name(env, var[0]) && to_print == 1)
	{
		replace_var(env, var[0], var[1]);
		return ;
	}
	if (ft_strcmp(var[1], ""))
		ft_addlast(env, var[0], var[1], to_print);
	else
		ft_addlast(env, var[0], "", to_print);
}

int	format_unset_ok(char *var)
{
	int		i;

	i = 0;
	if (ft_isalpha((int)var[0]) == 0 && var[0] != '_')
	{
		error_manager(ERNO_UNSET, var);
		g_status.exit_status = 1;
		return (0);
	}
	while (var[i] && (ft_isalnum(var[i]) == 1 || var[0] == '_'))
		i++;
	if (var[i] && ft_isalnum(var[i]) == 0 && var[0] != '_')
	{
		error_manager(ERNO_UNSET, var);
		g_status.exit_status = 1;
		return (0);
	}
	return (1);
}

void	ft_unset(t_env *env, char **name)
{
	int			i;
	char		*var;

	i = 1;
	while (name[i])
	{
		var = ft_strdup(name[i]);
		if (format_unset_ok(var))
		{
			if (existing_name(env, var))
				ft_rmvar(env, var);
		}
		free(var);
		i++;
	}
}
