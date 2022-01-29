/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:46:42 by vduriez           #+#    #+#             */
/*   Updated: 2022/01/29 16:47:27 by vduriez          ###   ########.fr       */
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

int	main(int ac, char **av)
{
	char	*term;
	int		exit_shell;

	(void)av;
	exit_shell = 1;
	if (ac != 1)
	{
		write(2, "Error\nTry with only	$> ./minishell\n", 37);
		return (0);
	}
	while (exit_shell > 0)
	{
		term = readline("mini-quack-shell\% ");
		if (!strcmp(term, "exit"))
			exit_shell = 0;
		free(term);
	}
	return (0);
}