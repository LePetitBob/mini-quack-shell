/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 01:56:16 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/03 03:21:42 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

// here : SIGINT = Ctrl-C
// here : SIGQUIT = Ctrl-'\'
void handler(int signum)
{
	if (signum == SIGINT)
	{
		
	}
	else if (signum == SIGQUIT)
	{
		
	}
}

// int		waitpidfunct()
// {
// 	int	ret;

// 	ret = 0;
// 	while (id)
// 	{
// 		waitpid(pid, &ret, OPTION)
// 		if (WIFSIGNAL)
// 			ret = ;
// 	}
// }
