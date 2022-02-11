/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:37:28 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/11 19:55:27 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	split_quotes_dollar(char *str, char *(**ret))
{
	char	*tmp;
	char	quote;
	int		i;

	i = 0;
	tmp = ft_strdup(str);
	ft_bzero(tmp, ft_strlen(str));
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			++i;
			while (str[i] != '\0' && str[i] != quote)
			{
				tmp[ft_strlen(tmp)] = str[i];
				++i;
			}
			if (quote == '\'')
				negate_spaces(&tmp);
			*ret = ft_add_tab(*ret, tmp);
			ft_bzero(tmp, ft_strlen(str));
		}
		else if (str[i] == '$')
		{
			tmp[ft_strlen(tmp)] = str[i];
			++i;
			if (ft_isalpha(str[i]) == 0)
			{
				tmp[ft_strlen(tmp)] = str[i];
				printf("char after $ is not alpha\n");
			}
			while (str[i] != '\0' && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
			{
				tmp[ft_strlen(tmp)] = str[i];
				++i;
			}
			*ret = ft_add_tab(*ret, tmp);
			ft_bzero(tmp, ft_strlen(str));
		}
		else
			++i;
	}
	free(tmp);
}

void	negate_spaces(char *(*str))
{
	int	i;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == ' ')
			(*str)[i] *= -1;
		++i;
	}
}
