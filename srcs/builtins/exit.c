/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:39:04 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/28 16:30:57 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

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

void	clear_and_exit(char **err, t_env *env)
{
	write(2, "mini-quack-shell: exit: ", 24);
	write(2, err[1], ft_strlen(err[1]));
	write(2, ": numeric argument required\n", 28);
	ft_freetab(err);
	rl_clear_history();
	ft_clear(env);
	exit(2);
}

void	ft_exit(char **err, t_env *env, int is_piped)
{
	int	errcode;
	int	i;

	errcode = EXIT_SUCCESS;
	if (!is_piped)
		write(1, "exit\n", 5);
	i = 0;
	while (err[i])
		i++;
	if (err[1])
	{
		if (is_num(err[1]))
			errcode = ft_atoi(err[1]);
		else
			clear_and_exit(err, env);
	}
	if (i <= 2)
	{
		ft_freetab(err);
		rl_clear_history();
		ft_clear(env);
		exit(errcode);
	}
	error_manager(ERNO_EXIT_ARGS, "exit");
}
