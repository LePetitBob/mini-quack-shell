/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:47:29 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/03 01:37:25 by amarini-         ###   ########.fr       */
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
	if (erno == ERNO_SYNTAX)
		err = get_syntax_error(str);
	else if (erno == ERNO_ISDIR || erno == ERNO_ACCESS || erno == ERNO_NOCMD
		|| erno == ERNO_ARGS || erno == ERNO_NOFILEDIR)
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
	if (erno == ERNO_PATH)
		pb = ft_strdup(": HOME not set\n");
	if (erno == ERNO_NOFILEDIR)
	{
		pb = ft_strjoin(cmd, ": No such file or directory\n");
		tmp = ft_strjoin("cd: ", pb);
	}
	else
		tmp = ft_strjoin(cmd, pb);
	free(pb);
	return (tmp);
}

char	*get_syntax_error(char *str)
{
	char	*tmp;
	char	*pb;

	tmp = ft_strjoin("`", str);
	pb = ft_strjoin(tmp, "\'");
	free(tmp);
	tmp = ft_strjoin("syntax error near unexpected token ", pb);
	free(pb);
	pb = ft_strjoin(tmp, "\n");
	free(tmp);
	return (pb);
}
