/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 01:56:16 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/05 12:44:42 by amarini-         ###   ########.fr       */
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
	int	tmp;

	if (signum == SIGINT)
	{
		if (g_status.hd_fd == STDIN_FILENO)
		{
			tmp = dup(STDIN_FILENO);
			close(STDIN_FILENO);
			g_status.hd_fd = tmp;
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		else
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_replace_line("", STDOUT_FILENO);
			rl_on_new_line();
			rl_redisplay();
		}
		g_status.exit_status = 130;
	}
	if (signum == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
}

void	handler_child(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		g_status.exit_status = 130;
	}
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit: (core dumped)\n", STDERR_FILENO);
		g_status.exit_status = 131;
	}
}
