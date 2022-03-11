/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_albe_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:19:05 by amarini-          #+#    #+#             */
/*   Updated: 2022/03/11 11:45:49 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

void	ft_print_tab(char **tab);

char	*ft_strdup(const char *s1);
char	*ft_del_one(char *str, int index);
char	*ft_strchr(const char *s, int c);
int		ft_strsrch(char *str, char c);

int		calc_row(char const *s, char sep);
int		calc_word(char const *s, char sep, int strpos);
char	*fill_array(char *result, char const *s, int i, char sep);
char	**free_everything(char **result);
char	**ft_split(char const *s, char c);

int		ft_strcmp(const char *s1, const char *s2);

void	del_quotes(char **str, int *first, int second)
{
	char	*tmp;

	tmp = ft_del_one(*str, (*first) + second);
	free(*str);
	(*str) = ft_strdup(tmp);
	free(tmp);
	tmp = ft_del_one(*str, *first);
	free(*str);
	(*str) = ft_strdup(tmp);
	free(tmp);
	(*first) += ((*first) - second);
	return ;
}

void	quote_manager(char **str)
{
	int	i;
	int	pair;

	i = 0;
	while ((*str)[i] != '\0')
	{
		pair = 1;
		if ((*str)[i] == '\'')
		{
			while ((*str)[i + pair] != '\0' && (*str)[i + pair] != '\'')
				++pair;
			if ((*str)[i + pair] == '\'')
				del_quotes(str, &i, pair);
		}
		else if ((*str)[i] == '\"')
		{
			while ((*str)[i + pair] != '\0' && (*str)[i + pair] != '\"')
				++pair;
			if ((*str)[i + pair] == '\"')
				del_quotes(str, &i, pair);
		}
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
		quote_manager(&str);
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
