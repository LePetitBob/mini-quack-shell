/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_seps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:50:22 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/11 12:12:27 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"


void	split_seps(char *(**args))
{
	int		i;
	int		i_sep;

	i = 0;
	while ((*args)[i])
	{
		if (ft_strsrch((*args)[i], '\'') == -1
			&& ft_strsrch((*args)[i], '\"') == -1)
		{
			if (ft_strsrch((*args)[i], '|') != -1)
				separate_separator(args, "|", i);
			if (ft_strsrch((*args)[i], '<') != -1)
			{
				i_sep = ft_strsrch((*args)[i], '<') + 1;
				if ((*args)[i][i_sep] == '<')
					separate_separator(args, "<<", i);
				else
					separate_separator(args, "<", i);
			}
			if (ft_strsrch((*args)[i], '>') != -1)
			{
				i_sep = ft_strsrch((*args)[i], '>') + 1;
				if ((*args)[i][i_sep] == '>')
					separate_separator(args, ">>", i);
				else
					separate_separator(args, ">", i);
			}
		}
		++i;
	}
}

void	separate_separator(char *(**args), char *sep, int i_args)
{
	char	*tmp;
	int		sep_index;

	if (ft_strcmp((*args)[i_args], sep) == 0)
		return ;
	sep_index = ft_strsrch((*args)[i_args], sep[0]);
	if (sep_index > 0)
	{
		tmp = ft_strndup((*args)[i_args], sep_index);
		*args = ft_insert_tab(*args, tmp, i_args);
		++i_args;
		while(tmp[0] != sep[0])
		{
			free(tmp);
			tmp = ft_del_one((*args)[i_args], 0);
			free((*args)[i_args]);
			(*args)[i_args] = ft_strdup(tmp);
		}
		free(tmp);
		sep_index = 0;
	}
	tmp = ft_del_one((*args)[i_args], sep_index);
	if (ft_strlen(sep) > 1)
		tmp = ft_del_one(tmp, sep_index);
	free((*args)[i_args]);
	(*args)[i_args] = ft_strdup(sep);
	*args = ft_insert_tab(*args, tmp, i_args + 1);
	free(tmp);
}
