/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_tmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:25:38 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/23 02:29:21 by vduriez          ###   ########.fr       */
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

char	*ft_strndup(const char *s1, int n)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (s1[i] && i < (int)n)
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	while (j < i)
	{
		res[j] = s1[j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

int	is_num(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
		i++;
	}
	return (1);
}
