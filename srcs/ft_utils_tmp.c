/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_tmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:25:38 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/10 10:44:13 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

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
	size_t		i;
	size_t		j;
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

char	*ft_strndup(const char *s1, size_t n)
{
	size_t		i;
	size_t		j;
	char	*res;

	i = 0;
	j = 0;
	while (s1[i] && i < n)
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
	free(s[i]);
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

int		ft_count_word(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != 0)
	{
		if (ft_strchar(str[i], c) != -1)
			i++;
		else
		{
			count++;
			while (ft_strchar(str[i], c) == -1 && str[i] != 0)
			{
				i++;
			}
		}
	}
	return (count);
}

char	**ft_split(char const *str, char c)
{
	char	**splited;
	int		i;
	int		j;
	int		k;

	if (!str)
		return (NULL);
	k = 0;
	i = 0;
	if (!(splited = malloc(sizeof(char *) * (ft_count_word(str, c) + 1))))
		return (0);
	while (i < ft_count_word(str, c) && str[0] != 0)
	{
		j = 0;
		while (ft_strchar(str[k], c) != -1 && str[k] != 0)
			k++;
		if (!(splited[i] = malloc(sizeof(char) * (ft_size_w(str, k, c) + 1))))
			return (0);
		while (ft_strchar(str[k], c) == -1 && str[k] != 0)
			splited[i][j++] = str[k++];
		splited[i][j] = '\0';
		i++;
	}
	splited[i] = 0;
	return (splited);
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

int	ft_atoi(const char *str)
{
	int i;
	int signe;
	int somme;

	i = 0;
	signe = 1;
	somme = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' ||
			str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		i++;
		signe = -1;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		somme = 10 * somme + (str[i] - 48);
		i++;
	}
	return (somme * signe);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	if (!(s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = 0;
	return (s3);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s1[i] != s2[i])
		return (1);
	return (0);
}