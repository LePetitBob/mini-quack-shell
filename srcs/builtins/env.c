/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:25:51 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/02 00:12:54 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	ft_env(t_env *env)
{
	t_env_var	*tmp;

	tmp = env->first;
	while (tmp)
	{
		if (tmp->to_print == 1)
		{
			write(1, tmp->name, ft_strlen(tmp->name));
			write(1, "=", 1);
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
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
		ft_addlast(env, env_split[0], env_split[1], 1);
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
		if (tmp_env->to_print == 1)
			i++;
		tmp_env = tmp_env->next;
	}
	return (i);
}

char	*get_env_arr(t_env_var *tmp_env)
{
	char	*tmp[3];
	char	*res;

	tmp[0] = ft_strdup(tmp_env->name);
	tmp[1] = ft_strjoin(tmp[0], "=");
	tmp[2] = ft_strdup(tmp_env->value);
	res = ft_strjoin(tmp[1], tmp[2]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	return (res);
}

char	**env_cl_to_arr(t_env *env)
{
	int			i;
	char		**env_arr;
	t_env_var	*tmp_env;

	i = env_size(env);
	env_arr = malloc(sizeof(char *) * (i + 1));
	env_arr[i] = NULL;
	i = 0;
	tmp_env = env->first;
	while (tmp_env)
	{
		if (tmp_env->to_print)
		{
			env_arr[i] = get_env_arr(tmp_env);
			i++;
		}
		tmp_env = tmp_env->next;
	}
	return (env_arr);
}
