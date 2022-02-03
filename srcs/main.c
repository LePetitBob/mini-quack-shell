/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:46:42 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/03 18:27:27 by vduriez          ###   ########.fr       */
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
	(void)ac;
	exit_shell = 1;
	get_env(envp, &env);
	//TODO 			if (!env) -> create PWD=le pwd, _=usr/bin/env, SHLVL=1
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
			free(term);
			if (!strcmp(cmd[0], "exit"))
				ft_exit(cmd, &env);
			else
			{
				if (!strcmp(cmd[0], "pwd"))
					ft_pwd(cmd);
				else if (term && !strcmp(cmd[0], "env"))
					ft_env(&env);
				else if (!strcmp(cmd[0], "echo"))
					ft_echo(cmd);
				else if (term && !strcmp(cmd[0], "export"))
					ft_export(&env, cmd);
				else if (term && !strcmp(cmd[0], "unset"))
					ft_unset(&env, cmd);
				else if (!strcmp(cmd[1], "cd"))
					ft_cd(cmd, envp);
				else
				{
					pid = fork();
					if (!pid)
					{
						if (env.first)
							ft_clear(&env);
						//TODO if (not_builtin) --> exec
						ft_exec(cmd, envp);
					}
					waitpid(pid, NULL, 0);
				}
			}
			ft_free(cmd);
		}
		else
			free(term);
	}
	return (0);
}