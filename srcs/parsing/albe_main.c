/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   albe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:38:25 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/10 17:50:47 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

int	main(int ac, char **av, char *env[])
{
	char	*line;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		line = readline("mini-quack-shell$ ");
		split_manager(line);
	}
}

void	split_manager(char *line)
{
	char	**args;

	args = NULL;
	//split spaces '"
	split_whitespaces(line, &args);
	// ft_print_tab(args);
	// printf("\n");
	//split <><<>>|
	split_seps(&args);
	ft_print_tab(args);
	//next step
}
