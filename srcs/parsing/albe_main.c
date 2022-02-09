/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   albe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:38:25 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/09 19:49:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

int	main(int ac, char *av, char *env[])
{
	char	*line;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("mini-quack-shell$ ");
		split_manager(line);
	}
}

void	split_manager(char *line)
{
	char	**args;

	args = char	**split_whitespaces(line);
	ft_print_tab(args);
	//split spaces '"
	//split <><<>>|
	//next step
}
