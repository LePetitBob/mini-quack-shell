/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:43:19 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/04 16:27:39 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ducklinclude/mini-quack-shell.h"

int	format_unset_ok(char *var)
{
	int		i;
	int		j;
	char	*name;

	j = 0;
	i = 0;
	while (var[j] && ((var[j] > 64 && var[j] < 91)
		|| (var[j] > 96 && var[j] < 123) || (var[j] > 46
		&& var[j] < 58) || var[j] == '_'))
		j++;
	if (var[j])
	{
		while (var[i] && var[i] != '=')
			i++;
		write(2, "mini-quack-shell: `", 19);
		write(2, var, ft_strlen(var));
		write(2, "`: not a valid identifier\n", 26);
		return (0);
	}
	return (1);
}

void	ft_unset(t_env *env, char **name)
{
	int			i;
	int			j;
	char		*var;

	i = 1;
	while (name[i])
	{
		j = 0;
		while (name[i][j] && name[i][j] != '=')
			j++;
		var = ft_strndup(name[i], j);
		if (format_unset_ok(var))
		{
			if (existing_name(env, var))
				ft_rmvar(env, var);
		}
		free(var);
		i++;
	}
}
