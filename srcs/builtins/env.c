/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:25:51 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/24 15:30:33 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	ft_env(t_env *env)
{
	t_env_var	*tmp;

	tmp = env->first;
	while (tmp)
	{
		write(1, tmp->name, ft_strlen(tmp->name));
		write(1, "=", 1);
		write(1, tmp->value, ft_strlen(tmp->value));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

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

void	get_env(char **envp, t_env *env)
{
	int		i;
	int		j;
	char	**env_split;

	i = 0;
	env_split = malloc(sizeof(char *) * 2);
	if (!env_split)
		return ;
	env->first = NULL;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		env_split[0] = strndup(envp[i], j);
		env_split[1] = strdup(envp[i] + j + 1);
		ft_addlast(env, env_split[0], env_split[1]);
		free(env_split[0]);
		free(env_split[1]);
		i++;
	}
	free(env_split);
}

int	env_size(t_env *env)
{
	t_env_var	*tmp_env;
	int			i;

	i = 0;
	tmp_env = env->first;
	while (tmp_env)
	{
		i++;
		tmp_env = tmp_env->next;
	}
	return (i);
}

char	**env_cl_to_arr(t_env *env)
{
	int			i;
	char		**env_arr;
	char		*tmp[3];
	t_env_var	*tmp_env;

	i = env_size(env);
	env_arr = malloc(sizeof(char *) * (i + 1));
	env_arr[i] = NULL;
	i = 0;
	tmp_env = env->first;
	while (tmp_env)
	{
		tmp[0] = ft_strdup(tmp_env->name);
		tmp[1] = ft_strjoin(tmp[0], "=");
		tmp[2] = ft_strdup(tmp_env->value);
		env_arr[i] = ft_strjoin(tmp[1], tmp[2]);
		free(tmp[0]);
		free(tmp[1]);
		free(tmp[2]);
		i++;
		tmp_env = tmp_env->next;
	}
	return (env_arr);
}
