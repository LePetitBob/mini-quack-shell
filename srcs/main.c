/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:46:42 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/07 17:12:38 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ducklinclude/mini-quack-shell.h"

int	main(int ac, char **av, char **envp)
{
	char	*term;
	char	**cmd;
	pid_t	pid;
	t_env	env;

	(void)av;
	(void)ac;
	//TODO 			if (!env) -> create PWD=le pwd, _=usr/bin/env, SHLVL=1
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
			free(term);
			//?BACKUP BELOW
			if (is_builtin(cmd[0]))
				ft_builtins(cmd, &env, envp);
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
			//?BACKUP BELOW
			ft_free(cmd);
		}
		else
			free(term);
	}
	return (0);
}


			//? if (!ft_strcmp(cmd[0], "exit"))
			//? 	ft_exit(cmd, &env);
			//? else
			//? {
			//? 	if (!ft_strcmp(cmd[0], "pwd"))
			//? 		ft_pwd(cmd);
			//? 	else if (!ft_strcmp(cmd[0], "env"))
			//? 		ft_env(&env);
			//? 	else if (!ft_strcmp(cmd[0], "echo"))
			//? 		ft_echo(cmd);
			//? 	else if (!ft_strcmp(cmd[0], "export"))
			//? 		ft_export(&env, cmd);
			//? 	else if (!ft_strcmp(cmd[0], "unset"))
			//? 		ft_unset(&env, cmd);
			//? 	else if (!ft_strcmp(cmd[0], "cd"))
			//? 		ft_cd(cmd, &env);
			//? 	else
			//? 	{
			//? 		pid = fork();
			//? 		if (!pid)
			//? 		{
			//? 			if (env.first)
			//? 				ft_clear(&env);
			//? 			//TODO if (not_builtin) --> exec
			//? 			ft_exec(cmd, envp);
			//? 		}
			//? 		waitpid(pid, NULL, 0);
			//? 	}
			//? }