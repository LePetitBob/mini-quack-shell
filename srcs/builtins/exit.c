/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:39:04 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/06 19:45:45 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

void	ft_clear(t_env *env)
{
	t_env_var	*tmp;
	t_env_var	*index;

	rl_clear_history();
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

void	clear_and_exit(char **err, t_env *env, t_cmd_lst *cmds)
{
	error_manager(ERNO_EX_NUM, err[1]);
	ft_freetab(err);
	rl_clear_history();
	ft_clear(env);
	rm_cmds(cmds);
	exit(2);
}

void	quit(t_env *env, t_cmd_lst *cmds)
{
	rl_clear_history();
	ft_clear(env);
	rm_cmds(cmds);
	exit((unsigned char)g_status.exit_status);
}

void	ft_exit(char **err, t_env *env, int is_piped, t_cmd_lst *cmds)
{
	int	i;

	if (!is_piped)
		write(1, "exit\n", 5);
	i = 0;
	while (err[i])
		i++;
	if (err[1])
	{
		if (is_num(err[1]))
			g_status.exit_status = ft_atoi(err[1]);
		else
			clear_and_exit(err, env, cmds);
	}
	ft_freetab(err);
	if (i <= 2)
		quit(env, cmds);
	g_status.exit_status = 1;
	error_manager(ERNO_ARGS, "exit");
	if (is_piped)
		quit(env, cmds);
}
