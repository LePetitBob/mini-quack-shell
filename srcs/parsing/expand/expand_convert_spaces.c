/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_convert_spaces.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:56:15 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/14 15:56:35 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	convert_all_wsp(char *(**arr), int conv)
{
	convert_spaces(arr, ' ' * conv);
	convert_spaces(arr, '\t' * conv);
	convert_spaces(arr, '\n' * conv);
	convert_spaces(arr, '\v' * conv);
	convert_spaces(arr, '\f' * conv);
	convert_spaces(arr, '\r' * conv);
}

void	convert_spaces(char *(**arr), char space)
{
	int		row;
	int		col;

	row = 0;
	while ((*arr)[row])
	{
		col = 0;
		if ((*arr)[row] && ft_strsrch((*arr)[row], '\"') > -1)
			++row;
		else
		{
			while ((*arr)[row][col] != '\0')
			{
				if ((*arr)[row][col] == space)
					(*arr)[row][col] *= -1;
				++col;
			}
			++row;
		}
	}
	return ;
}
