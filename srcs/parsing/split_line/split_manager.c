/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:54:27 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/19 00:27:41 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"


void	split_manager(char *line, t_env *env)
{
	char	**args;
	int		i;

	args = NULL;
	i = 0;
	split_whitespaces(line, &args);
	if (!args)
		return ;
	free(line);
	split_seps(&args);
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0
			&& (i == 0 || args[i + 1] == NULL
			|| ft_strcmp(args[i + 1], "|") == 0))
		{
			error_manager(ERNO_PIPE);
			ft_freetab(args);
			return ;
		}
		++i;
	}
	tokenize_manager(&args, env);
}

