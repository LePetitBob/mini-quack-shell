/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:12:04 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/06 19:51:54 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

void	ft_echo(char **s)
{
	int	i;
	int	nl;

	nl = 1;
	if (s[1] && !ft_strncmp("-n", s[1], 2))
	{
		i = 2;
		while (s[1][i] == 'n')
			i++;
		if (!s[1][i])
			nl = 0;
	}
	i = 1;
	if (nl == 0)
		i++;
	while (s[i])
	{
		if ((nl == 0 && i != 2) || (nl == 1 && i != 1))
			write(1, " ", 1);
		write(1, s[i], ft_strlen(s[i]));
		i++;
	}
	if (nl == 1)
		write(1, "\n", 1);
	g_status.exit_status = 0;
}
