/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:38:25 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/11 20:16:41 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

t_status	g_status;

static void	launch_signal_global(void);
static char	*get_prompt_prefix(t_env *env);

// here : SIGINT = Ctrl-C
// here : SIGQUIT = Ctrl-'\'
int	main(int ac, char **av, char *envp[])
{
	char	*prompt_prefix;
	char	*line;
	t_env	env;

	(void)ac;
	(void)av;
	launch_signal_global();
	get_env(envp, &env);
	while (1)
	{
		prompt_prefix = get_prompt_prefix(&env);
		line = readline(prompt_prefix);
		free(prompt_prefix);
		if (!line)
		{
			ft_clear(&env);
			ft_putstr_fd("exit\n", 1);
			return (0);
		}
		if (line[0] != '\0')
			add_history(line);
		split_manager(line, &env);
	}
}

static void	launch_signal_global(void)
{
	g_status.exit_status = 0;
	g_status.pid = -1;
	g_status.hd_fd = -1;
	g_status.exec_minishell = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

static char	*get_prompt_prefix(t_env *env)
{
	char	*home;
	char	*pth;
	char	*tmp;

	home = get_env_name(env, "HOME");
	pth = get_env_name(env, "PWD");
	if (home && ft_strnstr(pth, home, ft_strlen(pth)) == pth)
	{
		tmp = ft_substr(pth, ft_strlen(home), ft_strlen(pth) - ft_strlen(home));
		free(pth);
		pth = ft_strjoin("~", tmp);
		free(tmp);
	}
	tmp = ft_strjoin(pth, "$ ");
	free(pth);
	free(home);
	home = get_env_name(env, "USER");
	if (!home)
		home = ft_strdup("unknown");
	pth = ft_strjoin(home, ":");
	free(home);
	home = ft_strjoin(pth, tmp);
	free(pth);
	free(tmp);
	return (home);
}
