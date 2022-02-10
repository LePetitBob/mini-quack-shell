/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:16:30 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/10 19:55:23 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	redir(t_cmd *cmd)
{
	t_token	*tmp;
	int		err;

	err = 0;
	tmp = cmd->redir;
	while (tmp)
	{
		// if (tmp->type == HERE_DOC)
		// 	cmd->fdin = get here doc txt;
		if (tmp->type == RIN)
		{
			//TODO check errors with access
			cmd->fdin = open(tmp->str, O_RDONLY);
		}
		if (tmp->type == ROUT)
		{
			//TODO check errors with access
			cmd->fdout = open(tmp->str, O_WRONLY, O_TRUNC, O_CREAT, 0644);
		}
		if (tmp->type == DROUT)
		{
			//TODO check errors with access
			cmd->fdout = open(tmp->str, O_WRONLY, O_APPEND, O_CREAT, 0644);
		}
		if (err)
			break ;
		tmp = tmp->next;
	}
}