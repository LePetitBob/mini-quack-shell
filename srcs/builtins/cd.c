/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:43:15 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/01 21:24:23 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ducklinclude/mini-quack-shell.h"

void	ft_cd(char **cmd, char **envp)
{
	char	*path;
	char	*newpath;

	path = malloc(255 + 1);
	path[255] = 0;
	getcwd(path, 255);
	// if (!cmd[1])
	// chdir( -> to $(HOME));
	newpath = ft_strjoin(path, cmd[1]);
	chdir(newpath);
	free(newpath);
	free(path);
}