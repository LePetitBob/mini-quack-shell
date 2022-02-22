/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:38:04 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/22 11:39:10 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

t_token	*ft_create_empty_token(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->str = NULL;
	new->type = -1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_cmd	*ft_create_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	new->arg = NULL;
	new->redir = NULL;
	new->fdin = 0;
	new->fdout = 1;
	new->pid = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
