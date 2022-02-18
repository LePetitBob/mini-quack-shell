/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:54:27 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/18 17:05:32 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"


void	split_manager(char *line, t_env *env)
{
	char	**args;

	args = NULL;
	ft_putstr("_____line:\n[");
	ft_putstr(line);
	ft_putstr("]\n\n");
	split_whitespaces(line, &args);
	ft_putstr("_____split_whitespaces_seps:\n");
	split_seps(&args);
	ft_print_tab(args);
	ft_putstr("\n");
	tokenize_manager(&args, env);
}

