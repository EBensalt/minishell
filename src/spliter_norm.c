/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:40:50 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/18 23:38:27 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	cmd_fd_norm2(t_cmd *cmd, t_line *ptr)
{
	if (cmd->fd_o == -1)
	{
		printf("\033[0;31merror\033[0m : %s Is directory\n",
			ptr->next->value);
		g_exit = 7;
		return (1);
	}
	return (0);
}

int	cmd_fd_norm1(t_cmd *cmd, t_line *ptr)
{
	int	i;

	if (ptr->type == SO_RED)
	{
		if (cmd->fd_o != 1)
			close(cmd->fd_o);
		cmd->fd_o = open(ptr->next->value, O_CREAT | O_WRONLY | O_TRUNC,
				0644);
	}
	if (ptr->type == DO_RED)
	{
		if (cmd->fd_o != 1)
			close(cmd->fd_o);
		cmd->fd_o = open(ptr->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	if (cmd->fd_i == -1)
	{
		printf("\033[0;31merror\033[0m : %s no such file or directory\n",
			ptr->next->value);
		g_exit = 6;
		return (1);
	}
	i = cmd_fd_norm2(cmd, ptr);
	return (i);
}

void	cmd_fd_norm4(t_line *ptr, int fd[2])
{
	char	*str;
	int		i;

	while (1)
	{
		str = readline(">");
		if (ft_strcmp(str, ptr->next->value) == 0)
		{
			free(str);
			break ;
		}
		i = ft_strlen(str);
		write(fd[1], str, i);
		free(str);
	}
}

void	cmd_fd_norm3(t_cmd *cmd, t_line *ptr)
{
	int		fd[2];
	int		id;

	if (ptr->type == DI_RED)
	{
		pipe(fd);
		cmd->fd_i = fd[0];
		id = fork();
		if (id == 0)
		{
			close(fd[0]);
			if (cmd->fd_i != 0)
				close(cmd->fd_i);
			cmd_fd_norm4(ptr, fd);
			close(fd[1]);
			exit(0);
		}
		else
			wait(NULL);
	}
}

int	cmd_fd(t_line *line, t_cmd *cmd)
{
	t_line	*ptr;
	int		i;

	cmd->fd_i = 0;
	cmd->fd_o = 1;
	ptr = line;
	while (ptr && ptr->type != PIPE)
	{
		cmd_fd_norm3(cmd, ptr);
		if (ptr->type == SI_RED)
		{
			if (cmd->fd_i != 0)
				close(cmd->fd_i);
			cmd->fd_i = open(ptr->next->value, O_RDONLY);
		}
		i = cmd_fd_norm1(cmd, ptr);
		if (i != 0)
			return (i);
		ptr = ptr->next;
	}
	return (0);
}
