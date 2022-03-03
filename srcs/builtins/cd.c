/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:43:15 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/03 03:57:52 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

char	*get_in_env(t_env *env, char *name)
{
	t_env_var	*tmp;

	tmp = env->first;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	return (ft_strdup(tmp->value));
}

char	*create_path(t_env *env, char **cmd)
{
	char	*path;
	char	*tmp[3];

	tmp[0] = ft_strdup(cmd[1] + 1);
	tmp[1] = get_in_env(env, "HOME");
	tmp[2] = ft_strjoin(tmp[1], "/");
	path = ft_strjoin(tmp[2], tmp[0]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	return (path);
}

void	free_tmp(char **tmp)
{
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp[3]);
}

void	env_change_and_error_management(t_env *env, char **cmd, int i)
{
	char	*tmp[4];

	if (!cmd[1] && getenv("HOME"))
		chdir(getenv("HOME"));
	if (!cmd[1] && getenv("HOME"))
		return ;
	else if (cmd[1][0] == '~')
		tmp[2] = create_path(env, cmd);
	else
		tmp[2] = ft_strdup(cmd[1]);
	tmp[3] = getcwd(NULL, 0);
	i = chdir(tmp[2]);
	tmp[0] = get_in_env(env, "OLDPWD");
	tmp[1] = get_in_env(env, "PWD");
	if (i < 0)
		error_manager(ERNO_CD, cmd[1]);
	if (i >= 0 && tmp[0])
		replace_var(env, "OLDPWD", tmp[3]);
	free(tmp[3]);
	tmp[3] = getcwd(NULL, 0);
	if (i >= 0 && tmp[1])
		replace_var(env, "PWD", tmp[3]);
	free_tmp(tmp);
	g_status.exit_status = i;
}

void	ft_cd(char **cmd, t_env *env)
{
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		error_manager(ERNO_ARGS, "cd");
		g_status.exit_status = 1;
		return ;
	}
	if (!existing_name(env, "HOME"))
	{
		if (!cmd[1] || cmd[1][0] == '~')
		{
			error_manager(ERNO_PATH, "cd");
			g_status.exit_status = 1;
			return ;
		}
	}
	env_change_and_error_management(env, cmd, i);
}
