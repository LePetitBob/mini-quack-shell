/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:08:57 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/10 18:45:38 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "env"))
		return (1);
	return (0);
}

void	ft_exec(char **cmd, char **envp)
{
	int		i[2];
	char	**tmp_paths;
	char	*path[2];

	i[0] = 0;
	while (ft_strncmp(envp[i[0]], "PATH=", 5) != 0)
		i[0]++;
	if (envp[i[0]])
	{
		if (access(cmd[0], X_OK) == 0)
			execve(cmd[0], cmd + sizeof(char *), envp);
		tmp_paths = ft_split(envp[i[0]] + 5, ':');
		i[0] = 0;
		while (tmp_paths[i[0]])
		{
			path[0] = ft_strjoin(tmp_paths[i[0]], "/");
			path[1] = ft_strjoin(path[0], cmd[0]);
			if (access(path[1], X_OK) == 0)
				i[1] = execve(path[1], cmd, envp);
			i[0]++;
			free(path[0]);
			free(path[1]);
		}
	}
	printf("%s: command not found\n", cmd[0]);
	ft_free(tmp_paths);
	exit(errno); //TODO define if !rights or !existence with access
}

char	**get_cmd_str(t_cmd *cmd)
{
	int		i;
	char	**str_cmd;
	t_token	*tmp;

	i = 0;
	tmp = cmd->arg;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	str_cmd = malloc(sizeof(char *) * (i + 1));
	str_cmd[i] = NULL;
	tmp = cmd->arg;
	i = 0;
	while (tmp)
	{
		str_cmd[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	return (str_cmd);
}

void	execution(t_cmd *cmd, t_env *env)
{
	// int		i;
	// t_token	*tmp;
	char	**str_cmd;

	str_cmd = get_cmd_str(cmd);
	// if (is_builtin(str_cmd))
	// {
	// }
	// cmd->pid = fork();
	// if (!cmd->pid)
	// {
		ft_exec(str_cmd, env_cl_to_arr(env));
	// }
}