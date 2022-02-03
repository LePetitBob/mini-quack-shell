/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:43:15 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/03 14:03:08 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ducklinclude/mini-quack-shell.h"

void	ft_cd(char **cmd, char **envp)
{
	char	*path;
	char	*tmp[2];
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		write(2, "mini-quack-shell: cd: too many arguments\n", 41);
		return ;
	}
	// if (!getenv("HOME"))
	// {
	// 	if (!cmd[1] || cmd[1][0] == '~')
	// 		write(2, "mini-quack-shell: cd: HOME not set\n", 35);
	// 	if (!cmd[1] || cmd[1][0] == '~')
	// 		return (1);
	// }
	// if (!cmd[1] && getenv("HOME"))
	// 	chdir(getenv("HOME"));
	// if (!cmd[1] && getenv("HOME"))
	// 	return ;
	// else if (cmd[1][0] == '~')
	if (cmd[1][0] == '~')
	{
		tmp[0] = ft_strdup(cmd[1] + 1);
		tmp[1] = ft_strjoin(getenv("HOME"), "/");
		path = ft_strjoin(tmp[1], tmp[0]);
		ft_free(tmp);
	}
	path = ft_strdup(cmd[1]);
	chdir(path);
	free(path);
}