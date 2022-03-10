/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:44:46 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/10 17:04:37 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

void	ft_pwd(void)
{
	char	*path;

	g_status.exit_status = 0;
	path = getcwd(NULL, 0);
	if (!path)
		g_status.exit_status = 1;
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	free(path);
}
