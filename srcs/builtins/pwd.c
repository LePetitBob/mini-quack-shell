/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:44:46 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/02 17:09:13 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ducklinclude/mini-quack-shell.h"

void	ft_pwd(char **cmd)
{
	char	*path;

	// path = malloc(255 + 1);
	// path[255] = 0;
	// getcwd(path, 255);
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
}