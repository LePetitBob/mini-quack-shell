/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:26:55 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/19 03:59:55 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	get_here_doc(char *limiter)
{
	char	*here_doc_entry;
	int		fd_hd;

	chdir("objs/");
	fd_hd = open(HERE_DOC_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	here_doc_entry = readline("> ");
	while (ft_strcmp(limiter, here_doc_entry))
	{
		write(fd_hd, here_doc_entry, ft_strlen(here_doc_entry));
		write(fd_hd, "\n", 1);
		free(here_doc_entry);
		here_doc_entry = readline("> ");
	}
	close(fd_hd);
	chdir("../");
}