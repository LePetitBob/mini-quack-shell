/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:12:04 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/07 12:38:57 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

void	print_echo(int i, char **s)
{
	while (s[i])
	{
		write(1, s[i], ft_strlen(s[i]));
		i++;
		if (s[i])
			write(1, " ", 1);
	}
}

void	ft_echo(char **s)
{
	int	nl;
	int	i;
	int	j;

	nl = 1;
	j = 1;
	while (s[j] && !ft_strncmp("-n", s[j], 2))
	{
		i = 2;
		while (s[j][i] == 'n')
			i++;
		if (!s[j][i])
			nl = 0;
		if (!s[j][i])
			j++;
		else
			break ;
	}
	i = j;
	print_echo(i, s);
	if (nl == 1)
		write(1, "\n", 1);
	g_status.exit_status = 0;
}
