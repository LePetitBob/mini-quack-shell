/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:57:20 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/08 15:06:10 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

t_token	*ft_create_empty_token(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->str = NULL;
	new->type = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_cmd	*ft_create_cmd1(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	new->arg = NULL;
	new->redir = NULL;
	new->fdin = 0;
	new->fdout = 1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}