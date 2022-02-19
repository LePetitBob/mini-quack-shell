/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:00:30 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/19 03:55:17 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

char	*get_env_name(t_env *env, char *name)
{
	t_env_var	*tmp;

	tmp = env->first;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	existing_name(t_env *env, char *name)
{
	t_env_var	*tmp;

	tmp = env->first;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	format_export_ok(char *var)
{
	int		i;
	int		j;
	char	*name;

	j = 0;
	i = 0;
	while (var[j] && var[j] != '=' && ((var[j] > 64 && var[j] < 91)
			|| (var[j] > 96 && var[j] < 123) || (var[j] > 46
				&& var[j] < 58) || var[j] == '_'))
		j++;
	if ((var[j] && var[j] != '=') || (var[0] < 65 || var[0] > 122
			|| (var[0] > 90 && var[0] < 97)))
	{
		while (var[i] && var[i] != '=')
			i++;
		name = strndup(var, i);
		write(2, "mini-quack-shell: `", 19);
		write(2, name, ft_strlen(name));
		write(2, "`: not a valid identifier\n", 26);
		free(name);
		//! g_exit_status = 1;
		return (0);
	}
	return (1);
}

void	replace_var(t_env *env, char *name, char *value)
{
	t_env_var	*tmp;

	tmp = env->first;
	while (ft_strcmp(tmp->name, name))
		tmp = tmp->next;
	free(tmp->value);
	if (value)
		tmp->value = ft_strdup(value);
	else
		tmp->value = ft_strdup("");
}

void	add_env_var(t_env *env, char **var)
{
	if (existing_name(env, var[0]))
	{
		replace_var(env, var[0], var[1]);
		return ;
	}
	if (ft_strcmp(var[1], ""))
		ft_addlast(env, var[0], var[1]);
	else
		ft_addlast(env, var[0], "");
}

void	ft_export(t_env *env, char **cmd)
{
	int		i[2];
	char	*var[2];

	i[0] = 0;
	while (cmd[i[0]])
	{
		if (format_export_ok(cmd[i[0]]))
		{
			i[1] = 0;
			while (cmd[i[0]][i[1]] && cmd[i[0]][i[1]] != '=')
				i[1]++;
			if (cmd[i[0]][i[1]] && cmd[i[0]][i[1]] == '=')
			{
				var[0] = ft_strndup(cmd[i[0]], i[1]);
				if (!cmd[i[0]][i[1] + 1])
					var[1] = ft_strdup("");
				else
					var[1] = ft_strdup(cmd[i[0]] + i[1] + 1);
				add_env_var(env, var);
				free(var[0]);
				free(var[1]);
			}
		}
		i[0]++;
	}
}
