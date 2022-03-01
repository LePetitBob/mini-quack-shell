/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:26:55 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/01 02:05:40 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

void	get_here_doc(char *limiter)
{
	char	*here_doc_entry;
	int		fd_hd;

	chdir("objs/");
	fd_hd = open(HERE_DOC_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// dprintf(2, "writing in fd_here_doc %d\n", fd_hd);
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

void	rm_here_doc_tmp_file(t_env *env, t_cmd_lst *cmds)
{
	pid_t		pidtmp;
	char		*tmp[3];
	char		**tmpenv;

	tmpenv = env_cl_to_arr(env);
	if (access(HERE_DOC_PATH, F_OK) == 0)
	{
		pidtmp = fork();
		if (!pidtmp)
		{
			tmp[0] = ft_strdup("rm");
			tmp[1] = ft_strdup(HERE_DOC_PATH);
			tmp[2] = NULL;
			ft_clear(env);
			ft_exec(tmp, tmpenv, cmds);
		}
	}
	ft_freetab(tmpenv);
}
