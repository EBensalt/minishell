/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_norm1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 08:56:57 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 15:17:55 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	cmd_fd_norm3(t_cmd *cmd, t_line *ptr, t_list *list)
{
	int		id;
	int		fd;

	if (ptr->type == DI_RED && !g_global.err)
	{
		fd = open("/tmp/minishell_heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0777);
		id = fork();
		if (id == 0)
		{
			signal(SIGINT, handler_herdock);
			cmd_fd_norm4(ptr, fd, list);
			close(fd);
			exit(0);
		}
		signal(SIGINT, SIG_IGN);
		wait(NULL);
		close(fd);
		cmd->fd_i = open("/tmp/minishell_heredoc", O_RDONLY);
		if (cmd->fd_i == -1)
		{
			g_global.err = 1;
			cmd->fd_i = 0;
		}
	}
}

int	cmd_fd(t_line *line, t_cmd *cmd, t_list *list)
{
	t_line	*ptr;
	int		i;

	cmd->fd_i = 0;
	cmd->fd_o = 1;
	ptr = line;
	while (ptr && ptr->type != PIPE)
	{
		cmd_fd_norm3(cmd, ptr, list);
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

void	cmd_fd_norm6(t_line *ptr)
{
	if (access(ptr->next->value, R_OK) && !access(ptr->next->value, F_OK))
	{
		write(2, "error : ", 8);
		ft_putstr_fd(ptr->next->value, 2);
		write(2, " Permission denied\n", 19);
	}
	else
	{
		write(2, "error : ", 8);
		ft_putstr_fd(ptr->next->value, 2);
		write(2, " no such file or directory\n", 27);
	}
	g_global.g_exit = 1;
}

int	cmd_fd_norm7(char *str, int fd, t_list *list)
{
	int		i;
	char	*env;
	int		tem;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
		{
			env = ft_itoa(g_global.g_exit_c);
			tem = ft_strlen(env);
			write(fd, env, tem);
			i += 2;
		}
		else
			i = cmd_fd_norm8(str, i, list, fd);
	}
	return (i);
}

int	cmd_fd_norm8(char *str, int i, t_list *list, int fd)
{
	char	*env;
	int		tem;

	if (str[i] == '$' && str[i + 1]
		&& ft_isalnum_1(str[i + 1]) == 1)
	{
		env = cmd_fd_norm5(str, i, list);
		if (env)
		{
			tem = ft_strlen(env);
			write(fd, env, tem);
		}
		while (ft_isalnum_1(str[++i]) == 1)
			;
		i--;
	}
	else
		write(fd, &str[i], 1);
	return (i);
}
