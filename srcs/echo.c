/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:12:04 by vduriez           #+#    #+#             */
/*   Updated: 2022/01/30 17:44:35 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ducklinclude/mini-quack-shell.h"

//TODO		A quotes remover function will be needed,
//TODO		see Duckumentation/duckuotes.txt

void	ft_echo(int n, char *s)
{
	if (n == 1)
		printf("%s\n", s);
	if (n == -1)
		printf("%s", s);	
}