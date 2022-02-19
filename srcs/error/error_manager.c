/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:47:29 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/18 19:12:54 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	error_manager(int erno)
{
	char	*prefix;
	char	*err;
	char	*final;

	prefix = ft_strdup("mini_quack_shell: ");
	if (erno == ERNO_QUOTE)
		err = ft_strdup("syntax error unclosed quote\n");
	else if (erno == ERNO_PIPE)
		err = ft_strdup("syntax error near unexpected token \'|\'\n");
	final = ft_strjoin(prefix, err);
	ft_putstr(final);
	free(prefix);
	free(err);
	free(final);
}
