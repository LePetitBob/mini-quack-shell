/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_error_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 06:00:18 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/25 05:06:07 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	get_error_redir(t_token *next)
{
	if (!next)
		error_manager(ERNO_NEWLINE, NULL);
	else if (next->type == RIN)
		error_manager(ERNO_RIN, NULL);
	else if (next->type == ROUT)
		error_manager(ERNO_ROUT, NULL);
	else if (next->type == DROUT)
		error_manager(ERNO_DROUT, NULL);
	else if (next->type == HERE_DOC)
		error_manager(ERNO_HERE_DOC, NULL);
}
