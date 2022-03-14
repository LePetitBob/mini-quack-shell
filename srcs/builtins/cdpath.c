/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpath.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:49:11 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/14 14:49:08 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

char	*create_cdpath(t_env *env, char **cmd)
{
	char	*path;
	char	*tmp[3];

	tmp[0] = ft_strdup(cmd[1]);
	tmp[1] = get_env_name(env, "CDPATH");
	tmp[2] = ft_strjoin(tmp[1], "/");
	path = ft_strjoin(tmp[2], tmp[0]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	return (path);
}

int	cdpath(char **cmd, t_env *env)
{
	char	*tmp[4];
	int		i;

	tmp[2] = create_cdpath(env, cmd);
	tmp[3] = getcwd(NULL, 0);
	i = chdir(tmp[2]);
	if (i == 0)
	{
		write(1, tmp[2], ft_strlen(tmp[2]));
		write(1, "\n", 1);
	}
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
	return (-i);
}
