/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:32:07 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/22 16:33:01 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

t_token	*get_last_token(t_token *tokens)
{
	t_token	*it;

	it = tokens;
	while (it->next)
		it = it->next;
	return (it);
}
