/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:43:15 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/03 23:02:30 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

char	*create_path(t_env *env, char **cmd)
{
	char	*path;
	char	*tmp[3];

	tmp[0] = ft_strdup(cmd[1] + 1);
	tmp[1] = get_env_name(env, "HOME");
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

void	cd_home(char *cdarg, char *home)
{
	if (!cdarg && home)
		chdir(home);
	if (home)
		free(home);
}

void	env_change_and_error_management(t_env *env, char **cmd, int i)
{
	char	*tmp[4];

	tmp[0] = get_env_name(env, "HOME");
	cd_home(cmd[1], tmp[0]);
	if (!cmd[1] && tmp[0])
		return ;
	else if (cmd[1][0] == '~')
		tmp[2] = create_path(env, cmd);
	else
		tmp[2] = ft_strdup(cmd[1]);
	tmp[3] = getcwd(NULL, 0);
	i = chdir(tmp[2]);
	tmp[0] = get_env_name(env, "OLDPWD");
	tmp[1] = get_env_name(env, "PWD");
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
		if (!cmd[1] || (cmd[1] && cmd[1][0] == '~'))
		{
			error_manager(ERNO_PATH, "cd");
			g_status.exit_status = 1;
			return ;
		}
	}
	env_change_and_error_management(env, cmd, i);
}
