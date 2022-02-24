/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:38:25 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/24 03:19:01 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

int	g_exit_status;

int	main(int ac, char **av, char *envp[])
{
	char	*prompt_prefix;
	char	*line;
	t_env	env;

	(void)ac;
	(void)av;
	g_exit_status = 0;
	get_env(envp, &env);
	while (1)
	{
		prompt_prefix = get_prompt_prefix(&env);
		line = readline(prompt_prefix);
		free(prompt_prefix);
		add_history(line);
		if (!line)
		{
			// dprintf(2, "!line from readline\n");
			ft_clear(&env);
			return (0);
		}
		split_manager(line, &env);
	}
}

char	*get_prompt_prefix(t_env *env)
{
	char	*home;
	char	*path;
	char	*tmp;

	home = get_env_name(env, "HOME");
	path = get_env_name(env, "PWD");
	if (home && ft_strnstr(path, home, ft_strlen(path)) == path)
	{
		tmp = ft_substr(path, ft_strlen(home), ft_strlen(path) - ft_strlen(home));
		free(path);
		path = ft_strjoin("~", tmp);
		free(tmp);
	}
	tmp = ft_strjoin(path, "$ ");
	free(path);
	free(home);
	home = get_env_name(env, "USER");
	if (!home)
		home = ft_strdup("noname");
	path = ft_strjoin(home, ":");
	free(home);
	home = ft_strjoin(path, tmp);
	free(path);
	free(tmp);
	return (home);
}
