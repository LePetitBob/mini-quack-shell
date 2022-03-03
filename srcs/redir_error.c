/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 01:10:12 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/03 04:04:41 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

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
