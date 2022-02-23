/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:38:25 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/23 07:12:33 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

int	g_exit_status;

int	main(int ac, char **av, char *envp[])
{
	char	*line;
	t_env	env;

	(void)ac;
	(void)av;
	g_exit_status = 0;
	get_env(envp, &env);
	while (1)
	{
		line = readline("mini-quack-shell$ ");
		add_history(line);
		if (!line)
		{
			dprintf(2, "!line from readline\n");
			ft_clear(&env);
			return (0);
		}
		split_manager(line, &env);
	}
}
