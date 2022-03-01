/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:47:29 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/01 01:36:27 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	error_manager(int erno, char *str)
{
	char	*prefix;
	char	*err;
	char	*final;

	if (!str)
		(void)str;
	prefix = ft_strdup("mini_quack_shell: ");
	if (erno == ERNO_S_QUOTE || erno == ERNO_D_QUOTE || erno == ERNO_PIPE
		|| erno == ERNO_RIN || erno == ERNO_HERE_DOC || erno == ERNO_ROUT
		|| erno == ERNO_DROUT || erno == ERNO_NEWLINE)
		err = get_syntax_error(erno);
	else if (erno == ERNO_ISDIR || erno == ERNO_ACCESS || erno == ERNO_NOCMD
		|| erno == ERNO_ARGS)
		err = get_cmd_error(erno, str);
	if (erno != ERNO_NOCMD)
		final = ft_strjoin(prefix, err);
	else
		final = ft_strdup(err);
	ft_putstr_fd(final, STDERR_FILENO);
	free(prefix);
	free(err);
	free(final);
}

char	*get_cmd_error(int erno, char *cmd)
{
	char	*tmp;
	char	*pb;

	if (erno == ERNO_ACCESS)
		pb = ft_strdup(": Permission denied\n");
	if (erno == ERNO_NOCMD)
		pb = ft_strdup(": command not found\n");
	if (erno == ERNO_ISDIR)
		pb = ft_strdup(": Is a directory\n");
	if (erno == ERNO_ARGS)
		pb = ft_strdup(": too many arguments\n");
	tmp = ft_strjoin(cmd, pb);
	free(pb);
	return (tmp);
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
