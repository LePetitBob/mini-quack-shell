/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:15:17 by vduriez           #+#    #+#             */
/*   Updated: 2022/01/31 14:22:50 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ducklinclude/mini-quack-shell.h"

t_env_var	*ft_create_elem(char *name, char *value)
{
	t_env_var	*new;

	new = malloc(sizeof(t_env_var));
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	ft_addfirst(t_env *env, char *name, char *value)
{
	t_env_var	*a;

	a = ft_create_elem(name, value);
	if (env->first)
		a->next = env->first;
	else
		a->next = NULL;
	env->first = a;
}

void	ft_addlast(t_env *env, char *name, char *value)
{
	t_env_var	*a;
	t_env_var	*tmp;

	a = ft_create_elem(name, value);
	a->next = NULL;
	tmp = env->first;
	if (env->first)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = a;
	}
	else
	{
		env->first = a;
	}
}

void	ft_rmfirst(t_env *env)
{
	t_env_var	*tmp;

	tmp = env->first;
	env->first = tmp->next;
	free(tmp);
}

void	ft_rmlast(t_env *env)
{
	t_env_var	*tmp;
	t_env_var	*tmp2;

	tmp = env->first;
	while (tmp->next)
		tmp = tmp->next;
	tmp2 = tmp->next;
	tmp->next = NULL;
	free(tmp2);
}
