/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:20:39 by vduriez           #+#    #+#             */
/*   Updated: 2022/02/01 18:26:12 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ducklinclude/mini-quack-shell.h"

void	ft_dupstep(int fdin, int fdout)
{
	dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
}

void	child_process(char **av, int *i, int *fd, char **envp)
{
	int	fdi;

	if (i[0] == 0)
	{
		fdi = open(av[1], O_RDONLY);
		if (fdi < 0)
			ft_exit(126, av[1]);
		ft_dupstep(fdi, fd[1]);
		close(fdi);
	}
	else if (i[0] == i[1] - 4)
	{
		fdi = open(av[i[1] - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fdi < 0)
			ft_exit(126, av[i[1] - 1]);
		ft_dupstep(fd[2], fdi);
		close(fdi);
	}
	else
		ft_dupstep(fd[2], fd[1]);
	ft_close_all(fd);
	ft_exec(av[i[0] + 2], envp);
}

void	pipe(char **envp, char **cmd)
{
	pid_t	pid[4096];
	int		i[3];
	int		fd[3];

	i[0] = -1;
	fd[2] = dup(STDIN_FILENO);
	while (++i[0] < ac - 3)
	{
		if (pipe(fd) < 0)
			ft_exit(127, "pipe");
		pid[i[0]] = fork();
		if (pid[i[0]] < 0)
			ft_exit(127, "fork");
		if (!pid[i[0]])
			child_process(av, fd, envp);
		close_pipe(fd);
	}
	close(fd[2]);
	i[0] = -1;
	while (++i[0] < ac - 3)
		waitpid(pid[i[0]], &i[2], 0);
	return (0);
}
