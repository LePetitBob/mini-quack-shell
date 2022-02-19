/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:47:29 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/19 06:32:00 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	error_manager(int erno)
{
	char	*prefix;
	char	*err;
	char	*final;

	prefix = ft_strdup("mini_quack_shell: ");
	if (erno == ERNO_S_QUOTE || erno == ERNO_D_QUOTE || erno == ERNO_PIPE
		|| erno == ERNO_RIN || erno == ERNO_HERE_DOC || erno == ERNO_ROUT
		|| erno == ERNO_DROUT || erno == ERNO_NEWLINE)
		err = get_syntax_error(erno);
	final = ft_strjoin(prefix, err);
	ft_putstr(final);
	free(prefix);
	free(err);
	free(final);
}

char	*get_syntax_error(int erno)
{
	char	*tmp;
	char	*pb;

	if (erno == ERNO_S_QUOTE)
		pb = ft_strdup("\'\'\'");
	else if (erno == ERNO_D_QUOTE)
		pb = ft_strdup("\'\"\'");
	else if (erno == ERNO_PIPE)
		pb = ft_strdup("\'|\'");
	else if (erno == ERNO_RIN)
		pb = ft_strdup("\'<\'");
	else if (erno == ERNO_HERE_DOC)
		pb = ft_strdup("\'<<\'");
	else if (erno == ERNO_ROUT)
		pb = ft_strdup("\'>\'");
	else if (erno == ERNO_DROUT)
		pb = ft_strdup("\'>>\'");
	else if (erno == ERNO_NEWLINE)
		pb = ft_strdup("\'newline\'");
	tmp = ft_strjoin("syntax error near unexpected token ", pb);
	free(pb);
	pb = ft_strjoin(tmp, "\n");
	free(tmp);
	return (pb);
}
