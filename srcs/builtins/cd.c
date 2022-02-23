/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:43:15 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/23 04:37:50 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern int	g_exit_status;

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

void	invalid_path(char **cmd)
{
	write(2, "mini-quack-shell: cd: ", 22);
	write(2, cmd[1], ft_strlen(cmd[1]));
	write(2, ": No such file or directory\n", 28);
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

void	env_change_and_error_management(t_env *env, char **cmd, int i)
{
	char	*path;
	char	*pwd;

	if (!cmd[1] && getenv("HOME"))
		chdir(getenv("HOME"));
	if (!cmd[1] && getenv("HOME"))
		return ;
	else if (cmd[1][0] == '~')
		path = create_path(env, cmd);
	else
		path = ft_strdup(cmd[1]);
	pwd = getcwd(NULL, 0);
	i = chdir(path);
	if (i < 0)
		invalid_path(cmd);
	else
	{
		replace_var(env, "OLDPWD", pwd);
		free(pwd);
		pwd = getcwd(NULL, 0);
		replace_var(env, "PWD", pwd);
	}
	free(pwd);
	free(path);
	g_exit_status = i;
}

void	ft_cd(char **cmd, t_env *env)
{
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		write(2, "mini-quack-shell: cd: too many arguments\n", 41);
		g_exit_status = 1;
		return ;
	}
	if (!existing_name(env, "HOME"))
	{
		if (!cmd[1] || cmd[1][0] == '~')
		{
			write(2, "mini-quack-shell: cd: HOME not set\n", 35);
			g_exit_status = 1;
			return ;
		}
	}
	env_change_and_error_management(env, cmd, i);
}
