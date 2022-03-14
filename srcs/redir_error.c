/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 01:10:12 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/14 15:55:11 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

int	invalid_filename(char *filename, char *FILENO, int *i)
{
	if (!access(filename, F_OK))
	{
		if ((!ft_strcmp(FILENO, "OUT") && !access(filename, W_OK))
			|| (!ft_strcmp(FILENO, "IN") && !access(filename, R_OK)))
			return (0);
		*i = 1;
		error_manager(ERNO_ACCESS, filename);
		g_status.exit_status = 1;
		return (1);
	}
	else if (!ft_strcmp(FILENO, "IN"))
	{
		*i = 1;
		error_manager(ERNO_NOFILEDIR, filename);
		g_status.exit_status = 1;
		return (1);
	}
	return (0);
}

void	cd_error_status(char **cmd, int i, t_env *env)
{
	char	*env_cdpath;

	env_cdpath = get_env_name(env, "CDPATH");
	if (env_cdpath && i < 0)
		g_status.exit_status = cdpath(cmd, env);
	else if (errno == EACCES && !env_cdpath)
	{
		error_manager(ERNO_ACCESS, cmd[1]);
		g_status.exit_status = 126;
	}
	else
		g_status.exit_status = -i;
	free(env_cdpath);
}
