/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:00:30 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/04 16:26:19 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ducklinclude/mini-quack-shell.h"

//TODO Check setenv & unsetenv

int	existing_name(t_env *env, char *name)
{
	t_env_var	*tmp;

	tmp = env->first;
	while (tmp)
	{
		if (!strcmp(tmp->name, name))
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
	if (var[j] && var[j] != '=')
	{
		while (var[i] && var[i] != '=')
			i++;
		name = strndup(var, i);
		write(2, "mini-quack-shell: `", 19);
		write(2, name, ft_strlen(name));
		write(2, "`: not a valid identifier\n", 26);
		free(name);
		return (0);
	}
	return (1);
}

void	replace_var(t_env *env, char *name, char *value)
{
	t_env_var	*tmp;

	tmp = env->first;
	while (strcmp(tmp->name, name))
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
	if (strcmp(var[1], ""))
		ft_addlast(env, var[0], var[1]);
	else
		ft_addlast(env, var[0], "");
}

void	ft_export(t_env *env, char **cmd)
{
	int		i;
	int		j;
	char	*var[2];

	i = 0;
	while (cmd[i])
	{
		if (format_export_ok(cmd[i]))
		{
			j = 0;
			while (cmd[i][j] && cmd[i][j] != '=')
				j++;
			if (cmd[i][j] && cmd[i][j] == '=')
			{
				var[0] = ft_strndup(cmd[i], j);
				if (!cmd[i][j + 1])
					var[1] = ft_strdup("");
				else
					var[1] = ft_strdup(cmd[i] + j + 1);
				add_env_var(env, var);
				free(var[0]);
				free(var[1]);
			}
		}
		i++;
	}
	// int		i;
	// int		j;
	// int		k;

	// i = 1;
	// while (cmd[i])
	// {
	// 	j = 0;
	// 	k = 0;
	// 	while (cmd[i][k] != '=' && cmd[i][k])
	// 		k++;
	// 	while ((cmd[i][j] && ((cmd[i][j] > 64 && ((cmd[i][j] < 91)
	// 		|| (cmd[i][j] > 96 && cmd[i][j] < 123) || (cmd[i][j] > 46
	// 		&& cmd[i][j] < 58))) || cmd[i][j] == '_')) && i < k)
	// 		j++;
	// 	if (cmd[i][j] && cmd[i][j] != '=')
	// 	{
	// 		write(2, "mini-quack-shell: '", 19);
	// 		write(2, strncpy(cmd[i]), ft_strlen(cmd[i]));
	// 		write(2, "': not a valid identifier\n", 26);
	// 	}
	// 	else if (format_ok(cmd[i]))
	// 	{
	// 		add_env_var(env, cmd[i]);
	// 	}
	// 	i++;
	// }
}