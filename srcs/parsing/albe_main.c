/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   albe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:38:25 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/11 19:34:34 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

int	main(int ac, char **av, char *envp[])
{
	char	*line;
	t_env	env;

	(void)ac;
	(void)av;
	get_env(envp, &env);
	while (1)
	{
		line = readline("mini-quack-shell$ ");
		split_manager(line, env);
	}
}
