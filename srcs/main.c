/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:46:42 by vduriez           #+#    #+#             */
/*   Updated: 2022/01/31 18:53:19 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ducklinclude/mini-quack-shell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	main(int ac, char **av, char **envp)
{
	char	*term;
	int		exit_shell;
	t_env	env;

	(void)av;
	exit_shell = 1;
	if (ac != 1)
	{
		write(2, "Usage :\nThe programm requires no argument\ni.e. : $> ./minishell\n", 64);
		return (0);
	}
	get_env(envp, &env);
	while (1)
	{
		term = readline("mini-quack-shell$ ");
		add_history(term);
		// rl_clear_history();
		//TODO move rl_clear_history to ft_exit
		if (term && !strcmp(term, "exit"))
			ft_exit(term + 5);
		if (term && !strcmp(term, "exit"))
			ft_exit(term + 5);
		if (term && !strcmp(term, "pwd"))
			ft_pwd(envp);
		if (term && !strcmp(term, "env"))
			ft_env(&env);
		if (term && !strncmp(term, "cd ", 3))
			ft_cd(term + 3, envp);
		// if (term && !strncmp(term, "echo", 5))
		// 	ft_echo(term + 5);
		// if (term && !strncmp(term, "export", 6)))
		// 	ft_export_disp(&env);

		//TODO	if (check avec access)
		//TODO		exec
		free(term);
	}
	return (0);
}