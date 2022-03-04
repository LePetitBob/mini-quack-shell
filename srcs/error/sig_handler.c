/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 01:56:16 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/04 04:36:22 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

// here : SIGINT = Ctrl-C
// here : SIGQUIT = Ctrl-'\'
// child is actually never alive when the signal is sent :D
void	sig_handler(int signum)
{
	if (g_status.pid >= 0)
		handler_child(signum);
	else
		handler_parent(signum);
}

void	handler_parent(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_status.exit_status = 130;
	}
	if (signum == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 2);
}

void	handler_child(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_status.exit_status = 130;
	}
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit: (core dumped)\n", 2);
		g_status.exit_status = 131;
	}
}
