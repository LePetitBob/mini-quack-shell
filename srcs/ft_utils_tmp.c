/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_tmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:25:38 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/02 22:35:24 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

char	*get_path(char *path, char *cmd)
{
	char	*fullpath;
	char	*tmppath;

	tmppath = ft_strjoin(path, "/");
	fullpath = ft_strjoin(tmppath, cmd);
	free(tmppath);
	return (fullpath);
}

int	is_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+')
		i++;
	while (s[i])
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
		i++;
	}
	return (1);
}
