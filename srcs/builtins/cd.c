/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:43:15 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/10 17:28:04 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

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

void	ft_cd(char **cmd, t_env *env)
{
	char	*path;
	char	*pwd;
	char	*tmp[3];
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		write(2, "mini-quack-shell: cd: too many arguments\n", 41);
		return ;//! g_exit_status 1
	}
	if (!existing_name(env, "HOME"))
	{
		if (!cmd[1] || cmd[1][0] == '~')
			write(2, "mini-quack-shell: cd: HOME not set\n", 35);
		if (!cmd[1] || cmd[1][0] == '~')
			return ;//! g_exit_status 1
	}
	if (!cmd[1] && getenv("HOME"))
	{
		chdir(getenv("HOME"));
		return ;
	}
	else if (cmd[1][0] == '~')
	{
		tmp[0] = ft_strdup(cmd[1] + 1);
		tmp[1] = get_in_env(env, "HOME");
		tmp[2] = ft_strjoin(tmp[1], "/");
		path = ft_strjoin(tmp[2], tmp[0]);
		free(tmp[0]);
		free(tmp[1]);
		free(tmp[2]);
	}
	else
		path = ft_strdup(cmd[1]);
	pwd = getcwd(NULL, 0);
	i = chdir(path);
	if (i < 0)
	{
		write(2, "mini-quack-shell: cd: ", 22);
		write(2, cmd[1], ft_strlen(cmd[1]));
		write(2, ": No such file or directory\n", 28);
	}
	else
	{
		replace_var(env, "OLDPWD", pwd);
		free(pwd);
		pwd = getcwd(NULL, 0);
		replace_var(env, "PWD", pwd);
	}
	free(pwd);
	free(path);
	//! g_exit_status i
}