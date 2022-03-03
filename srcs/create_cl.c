/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:15:17 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/03 04:30:37 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

t_env_var	*ft_create_elem(char *name, char *value, int to_print)
{
	t_env_var	*new;

	new = malloc(sizeof(t_env_var));
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	new->to_print = to_print;
	return (new);
}

void	ft_addlast(t_env *env, char *name, char *value, int to_print)
{
	t_env_var	*a;
	t_env_var	*tmp;

	a = ft_create_elem(name, value, to_print);
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

void	ft_rmvar(t_env *env, char *var_name)
{
	t_env_var	*tmp;
	t_env_var	*tmp2;

	tmp = env->first;
	while (tmp->next && ft_strcmp(tmp->next->name, var_name))
		tmp = tmp->next;
	if (!tmp)
		return ;
	tmp2 = tmp->next;
	if (tmp->next->next)
		tmp->next = tmp->next->next;
	else
		tmp->next = NULL;
	free(tmp2->name);
	free(tmp2->value);
	free(tmp2);
}

void	replace_var(t_env *env, char *name, char *value)
{
	t_env_var	*tmp;

	tmp = env->first;
	while (ft_strcmp(tmp->name, name))
		tmp = tmp->next;
	if (tmp && tmp->value)
		free(tmp->value);
	if (tmp && value)
		tmp->value = ft_strdup(value);
	else if (tmp)
		tmp->value = ft_strdup("");
}
