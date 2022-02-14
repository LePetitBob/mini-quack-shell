/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:25:51 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/14 11:03:06 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

//TODO		Env doesnt update itself, we have to adjust it manually.
//TODO		After each command that do so (cd changes PWD and OLDPWD, modifying
//TODO		env variables, ...)

void	ft_env(t_env *env)
{
	t_env_var	*tmp;

	tmp = env->first;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
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