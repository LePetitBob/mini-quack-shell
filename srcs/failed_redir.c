/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failed_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 07:54:48 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/04 08:04:54 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

// void	abort_exec()
// {
// 	ft_freetab(cmd);
// 	rl_clear_history();
// 	ft_clear(env);
// 	rm_cmds(cmds);
// 	exit(g_status.exit_status);