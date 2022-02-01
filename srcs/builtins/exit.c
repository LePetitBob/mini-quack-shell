/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:39:04 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/01 15:14:04 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ducklinclude/mini-quack-shell.h"

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

void	ft_exit(char *err, t_env *env)
{
	int	errno;

	rl_clear_history();
	ft_clear(env);
	errno = 1;
	if (is_num(err))
		errno = ft_atoi(err);
	else
	{
		write(2, "mini-quack-shell: exit: one numeric argument required\n", 54);
		exit(1);
	}
	exit(errno);
}