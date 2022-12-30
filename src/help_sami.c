/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_sami.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 02:34:07 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 02:35:41 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

void	free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
}

int	ok_x_pathv2(t_list *list, DIR *dir, char **env, char **argv)
{
	int	pid;

	pid = 0;
	dir = opendir(argv[0]);
	if (access(argv[0], X_OK) == 0 && dir == NULL)
	{
		env = my_magic(list);
		pid = fork();
		if (pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			execve(argv[0], argv, env);
		}
		free_2d(env);
	}
	else
	{
		if (dir != NULL)
			closedir(dir);
		ft_putstr_fd("minishell: permission denied:", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}

void	ok_x_path(char **argv, t_list *list)
{
	struct stat	sb;
	char		**env;
	DIR			*dir;

	env = NULL;
	dir = NULL;
	if (argv[0] && lstat(argv[0], &sb) > -1)
	{
		ok_x_pathv2(list, dir, env, argv);
	}
	else
	{
		ft_putstr_fd("minishell: no such file or directory: ", 1);
		ft_putstr_fd(argv[0], 1);
		ft_putstr_fd("/n", 1);
	}
}

void	another_mini_help_for_mini2(char *commande)
{
	ft_putstr_fd("minishell: command not found: ", 1);
	ft_putstr_fd(commande, 1);
	ft_putstr_fd("\n", 1);
}

void	ft_mini_help_ft_trait(char **argv, t_list *list, char *commande)
{
	if (ft_strchr(argv[0], '/'))
		ok_x_path(argv, list);
	else
		another_mini_help_for_mini2(commande);
}
