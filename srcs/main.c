/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:38:25 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/22 14:34:46 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

int	g_exit_status;

int	main(int ac, char **av, char *envp[])
{
	char	*line;
	t_env	env;
	int i = 0;

	(void)ac;
	(void)av;
	g_exit_status = 0;
	get_env(envp, &env);
	while (1)
	{
		i++;
		write(2, ft_itoa(i), ft_countnbr(1, i));
		line = readline("mini-quack-shell$ ");
		add_history(line);
		if (!line)
		{
			dprintf(2, "!line frome readline\n");
			ft_clear(&env);
			return (0);
		}
		split_manager(line, &env);
		ft_putstr("__________done_everything:\n");
	}
}
