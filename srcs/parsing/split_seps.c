/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_seps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:50:22 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/10 19:27:05 by amarini-         ###   ########.fr       */
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
		// printf("\ni-[%d]\n", i);
		// ft_print_tab(*args);
		printf("\n");
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
		++i;
		printf("---------[%d][%s]\n", i, (*args)[i + 1]);
	}
	printf("\nFICHTREBITE\n");
}

void	separate_separator(char *(**args), char *sep, int i_args)
{
	char	*tmp;
	int		len_tmp;
	int		sep_index;
	int		i;

	i = 0;
	printf("arg-[%s]\n", (*args)[i_args]);
	if (ft_strcmp((*args)[i_args], sep) == 0)
		return ;
	sep_index = ft_strsrch((*args)[i_args], sep[0]);
	// printf("index_sep-[%d]\n", sep_index);
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
		// printf("insert prefix:\n");
		// ft_print_tab(*args);
		free(tmp);
		sep_index = 0;
	}
	if (sep_index == 0)
		sep_index = 1;
	len_tmp = ft_strlen((*args)[i_args]) - 1;
	tmp = (char *)malloc((len_tmp + 1) * sizeof(char));
	if (!tmp)
		return ;
	tmp[len_tmp] = '\0';
	while ((*args)[i_args][sep_index + i] != '\0' && i < len_tmp)
	{
		tmp[i] = (*args)[i_args][sep_index + i];
		++i;
	}
	// printf("\ntmp-[%s]\n", tmp);
	free((*args)[i_args]);
	(*args)[i_args] = ft_strdup(sep);
	*args = ft_insert_tab(*args, tmp, i_args + 1);
	// printf("\n");
	// ft_print_tab(*args);
	free(tmp);
}
