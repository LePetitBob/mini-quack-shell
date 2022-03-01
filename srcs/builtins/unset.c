/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:43:19 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/23 04:38:06 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern int	g_exit_status;

int	format_unset_ok(char *var, int *err)
{
	int		i;

	i = 0;
	while (var[i] && ((var[i] > 64 && var[i] < 91)
			|| (var[i] > 96 && var[i] < 123) || (var[i] > 46
				&& var[i] < 58)))
		i++;
	if (var[i] || (var[0] < 65 || var[0] > 122
			|| (var[0] > 90 && var[0] < 97)))
	{
		write(2, "mini-quack-shell: unset: `", 26);
		write(2, var, ft_strlen(var));
		write(2, "\': not a valid identifier\n", 26);
		*err = 1;
		return (0);
	}
	return (1);
}

void	ft_unset(t_env *env, char **name)
{
	int			i;
	int			j;
	int			err;
	char		*var;

	i = 1;
	err = 0;
	while (name[i])
	{
		j = 0;
		while (name[i][j] && name[i][j] != '=')
			j++;
		var = ft_strndup(name[i], j);
		if (format_unset_ok(var, &err))
		{
			if (existing_name(env, var))
				ft_rmvar(env, var);
		}
		free(var);
		i++;
	}
	g_exit_status = err;
}
