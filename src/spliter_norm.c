/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:40:50 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/28 02:13:28 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	cmd_fd_norm2(t_cmd *cmd, t_line *ptr)
{
	if (cmd->fd_o == -1)
	{
		if (opendir(ptr->next->value))
			printf("error : %s Is directory\n",
				ptr->next->value);
		else
		{
			printf("error : %s no such file or directory\n",
				ptr->next->value);
		}
		g_exit = 1;
		cmd->error = 1;
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
	if ((cmd->fd_i == -1 || cmd->fd_o == -1) && am_red == 2)
		return (1);
	if (cmd->fd_i == -1)
	{
		printf("error : %s no such file or directory\n",
			ptr->next->value);
		g_exit = 1;
		cmd->error = 1;
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
	tem = malloc(cnt * sizeof(char));
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
	int		tem;
	char	*env;

	while (1)
	{
		str = readline(">");
		if (ft_strcmp(str, ptr->next->value) == 0)
		{
			// free(str);
			break ;
		}
		if (heredoc == 0)
		{
			i = -1;
			while (str[++i])
			{
				if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
				{
					env = ft_itoa(g_exit_c);
					tem = ft_strlen(env);
					write(fd, env, tem);
					i += 2;
				}
				else if (str[i] == '$' && str[i + 1] && ft_isalnum_1(str[i + 1]) == 1)
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
			}
			write(fd, "\n", 1);
		}
		else
		{
			i = ft_strlen(str);
			write(fd, str, i);
			write(fd, "\n", 1);
		}
		// free(str);
	}
}

void	handler_herdock(int i)
{
	(void)i;
	unlink("/tmp/minishell_heredoc");
	exit(1);
}

void	cmd_fd_norm3(t_cmd *cmd, t_line *ptr, t_list *list)
{
	int		id;
	int		fd;

	if (ptr->type == DI_RED && !err)
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
			err = 1;
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
