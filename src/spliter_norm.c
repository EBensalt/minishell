/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:40:50 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 15:17:52 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	cmd_fd_norm2(t_cmd *cmd, t_line *ptr)
{
	DIR	*ptr0;

	if (cmd->fd_o == -1)
	{
		ptr0 = opendir(ptr->next->value);
		if (access(ptr->next->value, W_OK) && !access(ptr->next->value, F_OK))
		{
			write(2, "error : ", 8);
			ft_putstr_fd(ptr->next->value, 2);
			write(2, " Permission denied\n", 19);
		}
		else
			cmd_fd_norm9(ptr, ptr0);
		free(ptr0);
		g_global.g_exit = 1;
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
	if ((cmd->fd_i == -1 || cmd->fd_o == -1) && g_global.am_red == 2)
		return (1);
	if (cmd->fd_i == -1)
	{
		cmd_fd_norm6(ptr);
		return (1);
	}
	i = cmd_fd_norm2(cmd, ptr);
	return (i);
}

char	*cmd_fd_norm5(char *str, int i, t_list *list)
{
	char	*tem;
	char	*env;
	int		cnt;

	cnt = i;
	while (ft_isalnum_1(str[++cnt]) == 1)
		;
	cnt = cnt - i;
	tem = my_malloc(cnt * sizeof(char));
	cnt = -1;
	while (ft_isalnum_1(str[++i]) == 1)
		tem[++cnt] = str[i];
	tem[++cnt] = 0;
	env = my_getenv(tem, list);
	return (env);
}

void	cmd_fd_norm4(t_line *ptr, int fd, t_list *list)
{
	char	*str;
	int		i;

	while (1)
	{
		str = readline(">");
		if (ft_strcmp(str, ptr->next->value) == 0)
			break ;
		if (g_global.heredoc == 0)
		{
			i = cmd_fd_norm7(str, fd, list);
			write(fd, "\n", 1);
		}
		else
		{
			i = ft_strlen(str);
			write(fd, str, i);
			write(fd, "\n", 1);
		}
	}
}

void	handler_herdock(int i)
{
	(void)i;
	unlink("/tmp/minishell_heredoc");
	exit(1);
}
