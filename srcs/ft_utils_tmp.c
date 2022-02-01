/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_tmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:25:38 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/01 15:18:12 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ducklinclude/mini-quack-shell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while(s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 || !s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	if (!(res = malloc(sizeof(char) * i + 1)))
		return (NULL);
	while (j < i)
	{
		res[j] = s1[j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
}

int		ft_strchar(char c, char s)
{
	if (c == s)
		return (1);
	return (-1);
}

int		ft_size_w(const char *str, int i, char c)
{
	int	j;

	j = 0;
	while (ft_strchar(str[i], c) && str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

char	**ft_split(char const *str, char c)
{
	char	**splt;
	int		i;
	int		j;
	int		k;

	if (!str)
		return (NULL);
	k = 0;
	i = 0;
	if (!(splt = malloc(sizeof(char *) * 3)))
		return (0);
	while (i < 2 && str[0] != 0)
	{
		j = 0;
		while (ft_strchar(str[k], c) != -1 && str[k] != 0)
			k++;
		if (!(splt[i] = malloc(sizeof(char) * (ft_size_w(str, k, c) + 1))))
			return (0);
		while (ft_strchar(str[k], c) == -1 && str[k] != 0)
			splt[i][j++] = str[k++];
		splt[i][j] = '\0';
		i++;
	}
	splt[i] = 0;
	return (splt);
}

int	is_num(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < 48 || (s[i] > 57 && s[i] < 65) ||
					(s[i] > 90 && s[i] < 97) ||
					s[i] > 122)
			return (0);
		i++;
	}
	return (1);
}