/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:12:04 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/15 14:34:17 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	ft_echo(char **s)
{
	int	i;
	int	nl;

	nl = 1;
	if (s[1] && !strncmp("-n", s[1], 2))
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
			printf(" ");
		write(1, s[i], ft_strlen(s[i]));
		i++;
	}
	if (nl == 1)
		write(1, "\n", 1);
}
