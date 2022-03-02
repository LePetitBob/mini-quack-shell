/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:00:30 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/02 03:30:55 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern int	g_exit_status;

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

	i = 0;
	while (var[i] && var[i] != '=' && ((var[i] > 64 && var[i] < 91)
			|| (var[i] > 96 && var[i] < 123) || (var[i] > 46
				&& var[i] < 58)))
		i++;
	if ((var[i] && var[i] != '=') || (var[0] < 65 || var[0] > 122
			|| (var[0] > 90 && var[0] < 97)))
	{
		write(2, "mini-quack-shell: export: `", 27);
		write(2, var, ft_strlen(var));
		write(2, "\': not a valid identifier\n", 26);
		g_exit_status = 1;
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
	if (tmp && tmp->value)
		free(tmp->value);
	if (tmp && value)
		tmp->value = ft_strdup(value);
	else if (tmp)
		tmp->value = ft_strdup("");
}

void	export_display(t_env *env)
{
	t_env_var	*tmp;

	tmp = env->first;
	while (tmp)
	{
		write(1, tmp->name, ft_strlen(tmp->name));
		if (tmp->to_print == 1)
		{
			write(1, "=\"", 2);
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

void	ft_export(t_env *env, char **cmd)
{
	int		i[2];
	char	*var[2];

	i[0] = 1;
	if (!cmd[1])
	{
		export_display(env);
		return ;
	}
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
				add_env_var(env, var, 1);
			}
			else if (!cmd[i[0]][i[1]])
			{
				var[0] = ft_strdup(cmd[i[0]]);
				var[1] = ft_strdup("");
				add_env_var(env, var, 0);
			}
			free(var[0]);
			free(var[1]);
		}
		i[0]++;
	}
}
