/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sami.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:49:53 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 15:17:44 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

t_cmd	*command_creation(t_cmd *cmd, t_list *list)
{
	char	*str;
	char	**path;
	int		i;

	str = my_getenv("PATH", list);
	path = ft_split_exec(str, ':');
	i = -1;
	if (!path)
		return (cmd);
	str = ft_strdup(cmd->cmd);
	while (path[++i])
	{
		if (!access(ft_strjoin(path[i], cmd->cmd), F_OK))
		{
			cmd->cmd = ft_strjoin(path[i], cmd->cmd);
			cmd->cmd_line[0] = cmd->cmd;
			break ;
		}
	}
	cmd = command_creation_norm(cmd, str, i);
	return (cmd);
}

int	count_list(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

char	**env_creat(t_list *list)
{
	char	**env;
	int		i;

	env = my_malloc((count_list(list) + 1) * sizeof(char *));
	i = 0;
	while (list)
	{
		if (list->sepr == '=')
		{
			env[i] = ft_strjoin(list->first, "=");
			env[i] = ft_strjoin(env[i], list->second);
		}
		else
			env[i] = ft_strdup(list->first);
		i++;
		list = list->next;
	}
	return (env);
}

void	my_execve(t_cmd *cmd, t_list *list)
{
	char	*ptr;
	char	**env;

	env = NULL;
	ptr = ft_strdup(cmd->cmd);
	if (cmd->fd_i != 0)
	{
		dup2(cmd->fd_i, 0);
		close(cmd->fd_i);
	}
	if (cmd->fd_o != 1)
	{
		dup2(cmd->fd_o, 1);
		close(cmd->fd_o);
	}
	list = builtins_exec(cmd, list);
	my_execve_norm(cmd, list, env);
}

void	handler0(int i)
{
	if (i == SIGQUIT)
		write(2, "Quit: 3\n", 8);
}
