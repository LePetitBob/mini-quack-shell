/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 06:00:18 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/10 10:53:01 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

void	get_error_redir(t_token *next)
{
	if (!next)
		error_manager(ERNO_SYNTAX, "newline");
	else if (next->type == ROUT)
		error_manager(ERNO_SYNTAX, ">");
	else if (next->type == RIN)
		error_manager(ERNO_SYNTAX, "<");
	else if (next->type == DROUT)
		error_manager(ERNO_SYNTAX, ">>");
	else if (next->type == HERE_DOC)
		error_manager(ERNO_SYNTAX, "<<");
}

void	send_error_msg(char *str, int err, int exit_value)
{
	error_manager(err, str);
	g_status.exit_status = exit_value;
}

int	check_for_directory(char *str)
{
	int	i;

	i = 0;
	if (ft_strcmp(str, ".") == 0 || ft_strcmp(str, "..") == 0)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] != '/' && str[i] != '.')
			return (1);
		++i;
	}
	return (0);
}
