/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:26:55 by vduriez           #+#    #+#             */
/*   Updated: 2022/03/06 10:45:34 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_quack_shell.h"

extern t_status	g_status;

void	get_over_here_docs(t_cmd_lst *cmds, t_env *env, int *sig)
{
	t_cmd	*cmd;
	t_token	*redir;

	cmd = cmds->first;
	g_status.hd_fd = STDIN_FILENO;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir && g_status.hd_fd < 2)
		{
			if (redir->type == HERE_DOC)
				redir->str = get_here_doc(redir->str, env, sig);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	if (g_status.hd_fd > 2)
		dup2(g_status.hd_fd, STDIN_FILENO);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		j;
	char	*str;

	j = 0;
	if (!s1 && !s2)
		return (NULL);
	else if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2 && s1)
		return (ft_strdup(s1));
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str = fill_str(s1, str, j);
	j += ft_strlen(s1);
	str = fill_str(s2, str, j);
	j += ft_strlen(s2);
	str[j] = '\0';
	free(s1);
	return (str);
}

char	*here_doc_read(char *str, char *stock)
{
	char	*tmp[2];

	tmp[1] = NULL;
	tmp[0] = ft_strjoin(str, "\n");
	tmp[1] = ft_strjoin(stock, tmp[0]);
	free(tmp[0]);
	free(str);
	free(stock);
	return (tmp[1]);
}

char	*get_here_doc(char *limiter, t_env *env, int *sig)
{
	char		*tmp[2];

	tmp[0] = NULL;
	tmp[1] = NULL;
	while (ft_strcmp(limiter, tmp[0]))
	{
		if (tmp[0])
		{
			while (ft_strsrch(tmp[0], '$') != -1)
				expand_var(&tmp[0], env, 1);
			tmp[1] = here_doc_read(tmp[0], tmp[1]);
		}
		tmp[0] = readline("> ");
		if (tmp[0] == NULL)
			break ;
	}
	if (tmp[0])
		free(tmp[0]);
	free(limiter);
	if (g_status.hd_fd > 2)
		*sig = -2;
	return (tmp[1]);
}
