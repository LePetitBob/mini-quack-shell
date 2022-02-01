/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:46:42 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/01 21:25:10 by vduriez          ###   ########.fr       */
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
	char	**cmd;
	int		exit_shell;
	pid_t	pid;
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
		if(!term)
		{
			ft_clear(&env);
			exit(0);
		}
		if (term[0] != '\0')
		{
			cmd = ft_split(term, ' ');
			if (!strcmp(cmd[0], "exit"))
				ft_exit(cmd, &env);
			pid = fork();
			if (!pid)
			{
				if (env.first)
					ft_clear(&env);
				if (!strcmp(cmd[0], "pwd"))
					ft_pwd(cmd);
				// else if (term && !strcmp(cmd[0], "env"))
				// 	ft_env(&env);
				else if (!strncmp(cmd[0], "echo", 5))
					ft_echo(cmd);
				// else if (term && !strncmp(cmd[0], "export", 6)))
				// 	ft_export_disp(&env);
				else if (strncmp(cmd[0], "cd", 2))
					ft_exec(cmd, envp);
			}
			waitpid(pid, NULL, 0);
			if (!strncmp(cmd[0], "cd", 2))
				ft_cd(cmd, envp);
			ft_free(cmd);
		}
		free(term);
	}
	return (0);
}