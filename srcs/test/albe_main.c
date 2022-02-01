/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   albe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2022/02/01 17:19:05 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/01 18:49:55 by amarini-         ###   ########.fr       */
=======
/*   Created: 2022/02/01 15:54:38 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/01 17:15:29 by amarini-         ###   ########.fr       */
>>>>>>> dbd86f1b035a441e5cfd8e0cd02f4f60693f6a56
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
<<<<<<< HEAD
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

void	ft_print_tab(char **tab);

char	*ft_del_one(char *str, int index);
char	*ft_strchr(const char *s, int c);

int	calc_row(char const *s, char sep);
int	calc_word(char const *s, char sep, int strpos);
char	*fill_array(char *result, char const *s, int i, char sep);
char	**free_everything(char **result);
char	**ft_split(char const *s, char c);

int	ft_strcmp(const char *s1, const char *s2);

void	del_quotes(char **str, char quote)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while ((*str)[i] != '\0')
	{
		j = 0;
		while ((*str)[i] == quote && (*str)[j] != '\0')
		{
			if ((*str)[j] == quote && i != j)
			{
				tmp = ft_del_one(*str, i);
				free(*str);
				*str = tmp;
				tmp = ft_del_one(*str, j - 1);
				free(*str);
				*str = tmp;
				break ;
			}
			++j;
		}
		++i;
	}
}

int	main_manager(char *str, char *env[])
{
	int		i;
	char	**args;

	(void)env;
	i = 0;
	args = ft_split(str, ' ');
	ft_print_tab(args);
	while (args[i])
	{
		del_quotes(&args[i], '\'');
		del_quotes(&args[i], '\"');
		++i;
	}
	ft_print_tab(args);
	return (EXIT_SUCCESS);
=======
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	error(void)
{
	write(STDERR_FILENO, "error :D\n", 9);
	return (EXIT_FAILURE);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s1[i] != s2[i])
		return (1);
	return (0);
>>>>>>> dbd86f1b035a441e5cfd8e0cd02f4f60693f6a56
}

int	main(int ac, char **av, char *env[])
{
<<<<<<< HEAD
	char	*str;

	(void)ac;
	(void)av;
	while (1)
	{
		str = readline("mini-quack-shell$ ");
		if (ft_strcmp(str, "exit") == 0)
			return (EXIT_SUCCESS);
		main_manager(str, env);
	}
	return (EXIT_SUCCESS);
}
=======
	char	*args;

	while (1)
	{
		args = readline("mini-quack-shell$ ");
		if (ft_strcmp(args, "exit") == 0)
			return (EXIT_SUCCESS);
		
	}
	return (EXIT_SUCCESS);
}

int	main_manager(char *str, char *env[])
{
	int		i;
	char	**args;

	i = 0;
	args = ft_split()
	//parsing
	//resolution
	//here_doc
	//redirection
	//send
	return (EXIT_SUCCESS);
}
>>>>>>> dbd86f1b035a441e5cfd8e0cd02f4f60693f6a56
