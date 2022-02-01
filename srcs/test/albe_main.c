/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   albe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:19:05 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/01 18:49:55 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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
}

int	main(int ac, char **av, char *env[])
{
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
