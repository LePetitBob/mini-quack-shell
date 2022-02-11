/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:54:27 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/11 14:58:09 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"


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
	// ft_print_tab(args);
	//next step
	tokenize_manager(&args);
}

