/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sami_norm5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:46:59 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 15:22:55 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

t_cmd	*pipe_exec_norm2(t_cmd *cmd, t_cmd *ptr, int fd[2])
{
	if (cmd != ptr)
		close(cmd->tem);
	if (cmd->next)
		close(fd[1]);
	cmd = cmd->next;
	return (cmd);
}

void	pipe_exec_norm3(t_cmd *cmd, t_cmd *ptr, int fd[2], t_list *list)
{
	if (cmd->id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (cmd != ptr)
		{
			dup2(cmd->tem, 0);
			close(cmd->tem);
		}
		if (cmd->next)
		{
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
		}
		if (cmd && cmd->error == 0)
			my_execve(cmd, list);
		else
			exit(g_global.g_exit);
	}
}

int	ft_cd_norm(DIR *ptr, t_cmd *cmd, t_list *list, char *ptr0)
{
	ptr = opendir(cmd->cmd_line[1]);
	if (!ptr)
	{
		write(2, "minishell: ", 11);
		ft_putstr_fd(cmd->cmd_line[1], 2);
		write(2, ": No such file or directory\n", 28);
		g_global.g_exit = 1;
		return (1);
	}
	free(ptr->__dd_buf);
	free(ptr);
	change_pwd(list, "OLDPWD");
	chdir(cmd->cmd_line[1]);
	ptr0 = getcwd(NULL, 0);
	if (!ptr0)
	{
		write(2, "cd: error retrieving current directory: getcwd: ", 48);
		write(2, "cannot access parent directories: ", 34);
		write(2, "No such file or directory\n", 26);
		return (1);
	}
	free(ptr0);
	return (0);
}

int	ft_cd_norm1(DIR *ptr, t_list *list)
{
	if (!ptr)
	{
		write(2, "minishell: cd: ", 15);
		ft_putstr_fd(my_getenv("HOME", list), 2);
		write(2, ": No such file or directory\n", 28);
		g_global.g_exit = 1;
		return (1);
	}
	return (0);
}

void	delete_env_norm(t_list *ptr, t_list *ptr0)
{
	if (!ptr->next)
	{
		ptr0->next = NULL;
		free(ptr);
	}
	else
	{
		ptr0->next = ptr->next;
		free(ptr);
	}
}
