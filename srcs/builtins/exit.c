/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:39:04 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/01 18:58:14 by vduriez          ###   ########.fr       */
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
			free(tmp->name);
			free(tmp->value);
			free(tmp);
		}
	}
}

void	ft_exit(char **err, t_env *env)
{
	int	errno;
	int	i;

	rl_clear_history();
	ft_clear(env);
	errno = EXIT_SUCCESS;
	i = 0;
	if (err[1] && is_num(err[1]))
		errno = ft_atoi(err[1]);
	else if (err[1])
	{
		write(2, "mini-quack-shell: exit: numeric argument required\n", 50);
		ft_free(err);
		exit(2);
	}
	while (err[i])
		i++;
	if (i >= 2)
	{
		write(2, "too many arguments\n", 19);
		ft_free(err);
		exit(EXIT_FAILURE);
	}
	ft_free(err);
	exit(errno);
}