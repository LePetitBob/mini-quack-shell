/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:56:29 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/18 23:08:01 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	join_vars(char *(**arr))
{
	char	*joined;
	char	**tmp;
	char	**cpy;

	while ((*arr)[1])
	{
		ft_putstr("test:{");
		ft_print_tab(*arr);
		ft_putstr("}\n");
		joined = ft_strjoin((*arr)[0], (*arr)[1]);
		cpy = ft_erase((*arr), 0, 2);
		tmp = ft_insert_tab(cpy, joined, 0);
		free(joined);
		ft_freetab(*arr);
		*arr = ft_tabdup(tmp);
		ft_freetab(tmp);
	}
}
