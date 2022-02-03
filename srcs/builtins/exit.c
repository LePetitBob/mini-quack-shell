/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:39:04 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/02 17:06:07 by vduriez          ###   ########.fr       */
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
	int	errcode;
	int	i;

	errcode = EXIT_SUCCESS;
	write(2, "exit\n", 5);
	i = 0;
	while (err[i])
		i++;
	if (err[1])
	{
		if (is_num(err[1]))
			errcode = ft_atoi(err[1]);
		else
		{
			write(2, "mini-quack-shell: exit: ", 24);
			write(2, err[1], ft_strlen(err[1]));
			write(2, ": numeric argument required\n", 28);
			ft_free(err);
			rl_clear_history();
			ft_clear(env);
			exit(2);
		}
	}
	if (i <= 2)
	{
		ft_free(err);
		rl_clear_history();
		ft_clear(env);
		exit(errcode);
	}
	write(2, "too many arguments\n", 19);
}