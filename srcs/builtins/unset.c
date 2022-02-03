/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:43:19 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/03 18:25:20 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ducklinclude/mini-quack-shell.h"

void	ft_unset(t_env *env, char **name)
{
	t_env_var	*tmp;
	int			i;
	int			j;
	int			k;
	char		*var;

	i = 0;
	while (name[i])
	{
		if (format_ok(name[i]))
		{
			if (existing_name(env, name[i]))
				ft_rmvar(env, var);
		}
		i++;
	}
}
