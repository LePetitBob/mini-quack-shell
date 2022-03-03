/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:47:29 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/03 22:22:03 by amarini-         ###   ########.fr       */
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
	prefix = ft_strdup("minishell: ");
	if (erno == ERNO_SYNTAX)
		err = get_syntax_error(str);
	else if (erno == ERNO_ISDIR || erno == ERNO_ACCESS || erno == ERNO_NOCMD
		|| erno == ERNO_ARGS || erno == ERNO_NOFILEDIR || erno == ERNO_PATH)
		err = get_cmd_error(erno, str);
	else if (erno == ERNO_CD || erno == ERNO_UNSET || erno == ERNO_EXPORT
		|| erno == ERNO_EX_NUM)
		err = get_complex_error(erno, str);
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
	char	*pb;

	if (erno == ERNO_ACCESS)
		pb = ft_strjoin(cmd, ": Permission denied\n");
	else if (erno == ERNO_NOCMD)
		pb = ft_strjoin(cmd, ": command not found\n");
	else if (erno == ERNO_ISDIR)
		pb = ft_strjoin(cmd, ": Is a directory\n");
	else if (erno == ERNO_ARGS)
		pb = ft_strjoin(cmd, ": too many arguments\n");
	else if (erno == ERNO_PATH)
		pb = ft_strjoin(cmd, ": HOME not set\n");
	else if (erno == ERNO_NOFILEDIR)
		pb = ft_strjoin(cmd, ": No such file or directory\n");
	return (pb);
}

char	*get_complex_error(int erno, char *cmd)
{
	char	*tmp;
	char	*pb;

	if (erno == ERNO_CD)
	{
		pb = ft_strjoin(cmd, ": No such file or directory\n");
		tmp = ft_strjoin("cd: ", pb);
	}
	else if (erno == ERNO_UNSET || erno == ERNO_EXPORT)
	{
		pb = ft_strjoin(cmd, "\': not a valid identifier\n");
		if (erno == ERNO_UNSET)
			tmp = ft_strjoin("unset: `", pb);
		else
			tmp = ft_strjoin("export: `", pb);
	}
	else if (erno == ERNO_EX_NUM)
	{
		pb = ft_strjoin(cmd, ": numeric argument required\n");
		tmp = ft_strjoin("exit: ", pb);
	}
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
