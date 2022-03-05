/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failed_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 07:54:48 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/05 03:40:27 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

void	abort_exec(char **str_cmd, t_cmd *cmd, t_cmd_lst *cmds, t_env *env)
{
	if (cmd->fdin == -1 || cmd->fdout == -1
		|| cmd->fdin == -2 || cmd->fdout == -2)
	{
		ft_freetab(str_cmd);
		rl_clear_history();
		ft_clear(env);
		rm_cmds(cmds);
		exit(g_status.exit_status);
	}
}
