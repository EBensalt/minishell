/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sami_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 03:57:26 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 04:33:11 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

int	check_opt(char *str)
{
	int	i;

	i = 2;
	if (str && (str[0] == '-' && str[1] == 'n'))
	{
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

void	is_numeric(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i] != NULL)
	{
		while (args[1][j])
		{
			if ((args[1][0] == '-' || args[1][0] == '+') && args[1][1] == '0'
			&& !ft_atoi(&args[1][1]))
				(printf("exit\n"), exit(0));
			if (args[1][j] != '0' && !ft_atoi(&args[1][j]))
			{
				write(2, "exit\nminishell: exit: ", 22);
				write(2, args[1], ft_strlen(args[1]));
				write(2, ": numeric argument required\n", 28);
				exit(255);
			}
			j++;
		}
		i++;
	}
}

int	count_args(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i + 1);
}

int	ft_exit(char **args)
{
	long long	len;

	len = count_args(args);
	if (!args[1])
		(printf("exit\n"), exit(g_global.g_exit_c));
	is_numeric(args);
	write(2, &len, 4);
	if (len > 3)
		write(2, "exit\nminishell: exit: too many arguments\n", 41);
	else if (len == 3)
	{
		len = ft_atoi(args[1]);
		if (args[1][0] != '-' && len < 0)
		{
			write(2, "exit\nminishell: exit: ", 22);
			write(2, args[1], ft_strlen(args[1]));
			write(2, ": numeric argument required\n", 28);
			exit(255);
		}
		else
			(printf("exit\n"), exit(ft_atoi(args[1])));
	}
	g_global.g_exit = 1;
	return (1);
}

void	ft_echo(char **str)
{
	int	i;
	int	p;

	i = 1;
	p = 1;
	while (p)
	{
		p = check_opt(str[i]);
		if (p == 1)
			i++;
		else
			break ;
	}
	p = i;
	if (!str[i])
	{
		if (p != 1)
			return ;
		ft_putstr_fd("\n", 1);
		return ;
	}
	ft_echo_norm(str, i);
	if (p == 1)
		ft_putstr_fd("\n", 1);
}
