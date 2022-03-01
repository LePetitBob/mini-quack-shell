/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:50:22 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/01 22:40:23 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	split_seps(char *(**args))
{
	int		i;

	i = 0;
	while ((*args)[i])
	{
		if (ft_strsrch((*args)[i], '\'') == -1
			&& ft_strsrch((*args)[i], '\"') == -1)
		{
			if (ft_strsrch((*args)[i], '|') != -1)
				separate_separator(args, "|", i);
			if (ft_strsrch((*args)[i], '<') != -1
				|| ft_strsrch((*args)[i], '>') != -1)
				check_separator(args, i);
		}
		++i;
	}
}

void	check_separator(char *(**args), int i_args)
{
	int	i_seps;

	if (ft_strsrch((*args)[i_args], '<') != -1)
	{
		i_seps = ft_strsrch((*args)[i_args], '<') + 1;
		if ((*args)[i_args][i_seps] == '<')
			separate_separator(args, "<<", i_args);
		else
			separate_separator(args, "<", i_args);
	}
	else if (ft_strsrch((*args)[i_args], '>') != -1)
	{
		i_seps = ft_strsrch((*args)[i_args], '>') + 1;
		if ((*args)[i_args][i_seps] == '>')
			separate_separator(args, ">>", i_args);
		else
			separate_separator(args, ">", i_args);
	}
}

void	separate_separator(char *(**args), char *sep, int i_args)
{
	char	*tmp;
	char	*del_sep;

	tmp = NULL;
	if (ft_strcmp((*args)[i_args], sep) == 0)
		return ;
	if (ft_strsrch((*args)[i_args], sep[0]) > 0)
	{
		tmp = ft_strndup((*args)[i_args], ft_strsrch((*args)[i_args], sep[0]));
		*args = ft_insert_tab(*args, tmp, i_args);
		++i_args;
		while (tmp[0] != sep[0])
		{
			free(tmp);
			tmp = ft_del_one((*args)[i_args], 0);
			free((*args)[i_args]);
			(*args)[i_args] = ft_strdup(tmp);
		}
		free(tmp);
		tmp = NULL;
	}
	if (ft_strlen((*args)[i_args]) > 1)
		tmp = ft_del_one((*args)[i_args], ft_strsrch((*args)[i_args], sep[0]));
	if (ft_strlen(sep) > 1)
	{
		del_sep = ft_del_one(tmp, ft_strsrch((*args)[i_args], sep[0]));
		free(tmp);
		tmp = del_sep;
	}
	free((*args)[i_args]);
	(*args)[i_args] = ft_strdup(sep);
	*args = ft_insert_tab(*args, tmp, i_args + 1);
	free(tmp);
}
