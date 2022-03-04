/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:00:30 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/04 03:14:04 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

// ! pb here for "cd -" the name is actually correct
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
		error_manager(ERNO_EXPORT, var);
		g_status.exit_status = 1;
		return (0);
	}
	return (1);
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

void	export_var(int i[2], char **cmd, t_env *env)
{
	char	*var[2];

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

void	ft_export(t_env *env, char **cmd)
{
	int		i[2];

	i[0] = 1;
	if (!cmd[1])
	{
		export_display(env);
		return ;
	}
	while (cmd[i[0]])
	{
		if (format_export_ok(cmd[i[0]]))
			export_var(i, cmd, env);
		i[0]++;
	}
}
