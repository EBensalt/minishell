/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sami.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:49:53 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/19 00:09:33 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

void ft_exit()
{
    exit(0);
}

void    ft_echo(char **str)
{
    int i;

    i = 1;
    while (str[i])
    {
        ft_putstr_fd(str[i], 1);
        if (str[i + 1] != NULL)
            ft_putstr_fd(" ", 1);
        i++;
    }
    ft_putstr_fd("\n", 1);
}

void    ft_env(t_list *list)
{
    list->original = list;
    while (list->original)
    {
        ft_putstr_fd(list->original->first, 1);
        ft_putstr_fd("=", 1);
        ft_putstr_fd(list->original->second, 1);
        ft_putstr_fd("\n", 1);
        list->original = list->original->next;
    }
}

t_list	*ft_export(char *str, t_list *list)
{
	t_list	*tmp;

	tmp = NULL;
	list->original = list;
	while (list->original->next != NULL)
		list->original = list->original->next;
	tmp = new_list(str);
	list->original->next = tmp;
	return (list);
}

t_cmd	*command_creation(t_cmd *cmd)
{
	char	*str;
	char	**path;
	int		i;

	str = getenv("PATH");
	path = ft_split(str, ':');
	i = -1;
	while (path[++i])
	{
		if (!access(ft_strjoin(path[i], cmd->cmd), F_OK))
		{
			cmd->cmd = ft_strjoin(path[i], cmd->cmd);
			cmd->cmd_line[0] = cmd->cmd;
			break ;
		}
	}
	return (cmd);
}

t_list	*abdellatif_execution(t_cmd *cmd, t_list *list, char **env)
{
	int	id;
	// int	fd[2];

	// (void)env;
	if (cmd)
	{
		if (!ft_strcmp(cmd->cmd, "exit"))
			ft_exit();
		else if (!ft_strcmp(cmd->cmd, "echo"))
			ft_echo(cmd->cmd_line);
		else if (!ft_strcmp(cmd->cmd, "env"))
			ft_env(list);
		else if (!ft_strcmp(cmd->cmd, "export"))
			list = ft_export(cmd->cmd_line[1], list);
		else
		{
			id = fork();
			if (id == 0)
			{
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
				// printf("%d, %d, %d\n", cmd->fd_i, cmd->fd_o, i);
				cmd = command_creation(cmd);
				if (execve(cmd->cmd, cmd->cmd_line, env))
					printf("\033[0;31merror\033[0m : %s command not found\n",
						cmd->cmd);
				// exit(0);
			}
			else
				wait(NULL);
		}
	}
	return (list);
}
