/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:54:27 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/14 14:50:07 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"


void	split_manager(char *line, t_env *env)
{
	char	**args;

	args = NULL;
	ft_putchar('[');
	ft_putstr(line);
	ft_putstr("]\n\n");
	split_whitespaces(line, &args);
	split_seps(&args);
	ft_print_tab(args);
	ft_putstr("\n");
	tokenize_manager(&args, env);
}

