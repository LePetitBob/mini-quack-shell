/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:08:57 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/02 18:42:59 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ducklinclude/mini-quack-shell.h"

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
			ft_free(path);
		}
	}
	printf("%s: command not found\n", cmd[0]);
	ft_free(tmp_paths);
	exit(errno);
}