/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sami_norm4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:20:52 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 15:22:24 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

t_cmd	*command_creation_norm(t_cmd *cmd, char *str, int i)
{
	if (opendir(cmd->cmd))
	{
		write(2, "minishell: ", 11);
		ft_putstr_fd(cmd->cmd, 2);
		write(2, ": is a directory\n", 17);
		exit(126);
	}
	if (!ft_strcmp(cmd->cmd, str))
	{
		i = -1;
		if (cmd->cmd[1] == '/' && cmd->cmd[0] == '.')
			return (cmd);
		while (cmd->cmd[++i] && cmd->cmd[i] != '/')
			;
		if (!cmd->cmd[i])
		{
			write(2, "minishell: ", 11);
			ft_putstr_fd(cmd->cmd, 2);
			write(2, ": commad not found\n", 19);
			exit(126);
		}
	}
	return (cmd);
}

void	my_execve_norm(t_cmd *cmd, t_list *list, char **env)
{
	if (g_global.built == 1)
	{
		cmd = command_creation(cmd, list);
		env = env_creat(list);
		if (execve(cmd->cmd, cmd->cmd_line, env))
		{
			write(2, "minishell: ", 11);
			ft_putstr_fd(cmd->cmd, 2);
			write(2, ": ", 2);
			perror("");
		}
		exit(127);
	}
	else
		exit(0);
}

void	ft_echo_norm(char **str, int i)
{
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		if (str[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
}

void	pipe_exec_norm(t_cmd *ptr, int status)
{
	signal(SIGINT, handler0);
	signal(SIGQUIT, handler0);
	while (ptr)
	{
		waitpid(ptr->id, &status, 0);
		if (WIFEXITED(status))
			g_global.g_exit = WEXITSTATUS(status);
		else
			g_global.g_exit = 128 + WTERMSIG(status);
		ptr = ptr->next;
	}
}

t_cmd	*pipe_exec_norm1(t_cmd *cmd, t_cmd *ptr, int fd[2], t_list *list)
{
	cmd->id = fork();
	if (cmd->id == -1)
	{
		write(2, "error : fork :Resource temporarily unavailable\n", 47);
		return (0);
	}
	pipe_exec_norm3(cmd, ptr, fd, list);
	cmd = pipe_exec_norm2(cmd, ptr, fd);
	return (cmd);
}
