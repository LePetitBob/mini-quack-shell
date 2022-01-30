/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:46:42 by vduriez           #+#    #+#             */
/*   Updated: 2022/01/30 17:27:57 by vduriez          ###   ########.fr       */
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

	(void)av;
	exit_shell = 1;
	if (ac != 1)
	{
		write(2, "Usage :\nThe programm requires no argument\ni.e. : $> ./minishell\n", 64);
		return (0);
	}
	while (exit_shell > 0)
	{
		term = readline("mini-quack-shell$ ");
		if (term && !strcmp(term, "exit"))
			exit_shell = 0;
		if (term && !strcmp(term, "pwd"))
			ft_pwd(envp);
		if (term && !strcmp(term, "env"))
			ft_env(envp);
		if (term && !strncmp(term, "cd ", 3))
			ft_cd(term + 3, envp);
		if (term && !strncmp(term, "echo -n ", 8))
			ft_echo(-1, term + 8);
		else if (term && !strncmp(term, "echo ", 5))
			ft_echo(1, term + 5);
		if (term)
			free(term);
		else
			exit_shell = 0;
	}
	return (0);
}