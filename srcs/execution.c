/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:08:57 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/01 18:28:58 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ducklinclude/mini-quack-shell.h"

void	ft_exec(char **cmd, char **envp)
{
	int		i;
	int		tmp;
	char	**tmp_paths;
	char	*path;
	char	*path2;

	i = 0;
	tmp = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i])
	{
		if (access(cmd[0], X_OK) == 0)
			execve(cmd[0], cmd + sizeof(char *), envp);
		tmp_paths = ft_split(envp[i] + 5, ':');
		i = 0;
		while (tmp_paths[i])
		{
			path = ft_strjoin(tmp_paths[i], "/");
			path2 = ft_strjoin(path, cmd[0]);
			if (access(path2, X_OK) == 0)
				execve(path2, cmd, envp);
			i++;
			free(path);
			free(path2);
		}
	}
	printf("%s: command not found\n", cmd[0]);
	ft_free(tmp_paths);
	exit(EXIT_FAILURE);
}