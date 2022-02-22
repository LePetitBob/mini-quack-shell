/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:54:27 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/22 12:49:23 by vduriez          ###   ########.fr       */
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
	{
		free(line);
		return ;
	}
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
	ft_putstr("__________splited_str:\n{");
	ft_print_tab(args);
	ft_putstr("__________}\n");
	tokenize_manager(&args, env);
	ft_putstr("__________done_split:\n");
}
