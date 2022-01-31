/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:39:04 by vduriez           #+#    #+#             */
/*   Updated: 2022/01/31 18:55:03 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ducklinclude/mini-quack-shell.h"

void	ft_clear(t_env *env)
{
	t_env_var	*tmp;
	t_env_var	*index;

	if (env->first)
	{
		index = env->first;
		while (index)
		{
			tmp = index;
			index = index->next;
			free(tmp);
		}
	}
}

void	ft_exit(t_env *env, char *err)
{
	ft_clear(env);
	rl_clear_history();
	exit(ft_atoi(err));
}