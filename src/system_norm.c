/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 05:20:23 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 05:21:48 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

int	ft_joinandsearch(char *path, char *commande, char **argv, t_list *l)
{
	struct stat	sb;
	char		*newpath;
	char		**env;
	int			pid;

	if (commande[0] == '/')
		return (0);
	newpath = join_path(path, commande);
	if (lstat(newpath, &sb) > -1)
	{
		pid = fork();
		if (pid == 0)
		{
			env = my_magic(l);
			execve(newpath, argv, env);
		}
		free(newpath);
		return (1);
	}
	return (0);
}

int	search_commande(t_list *list, char *commande, char **argv)
{
	char	**path;
	int		len;

	path = NULL;
	len = 0;
	if (serach_env2(list))
	{
		path = ft_split(serach_env2(list), ':');
		len = 0;
		while (path[len])
		{
			if (ft_joinandsearch(path[len++], commande, argv, list) == 1)
				return (1);
		}
	}
	return (0);
}
