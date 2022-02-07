/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   albe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:54:38 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/01 17:15:29 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	error(void)
{
	write(STDERR_FILENO, "error :D\n", 9);
	return (EXIT_FAILURE);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s1[i] != s2[i])
		return (1);
	return (0);
}

int	main(int ac, char **av, char *env[])
{
	char	*args;

	while (1)
	{
		args = readline("mini-quack-shell$ ");
		if (ft_strcmp(args, "exit") == 0)
			return (EXIT_SUCCESS);
		
	}
	return (EXIT_SUCCESS);
}

int	main_manager(char *str, char *env[])
{
	int		i;
	char	**args;

	i = 0;
	args = ft_split()
	//parsing
	//resolution
	//here_doc
	//redirection
	//send
	return (EXIT_SUCCESS);
}
