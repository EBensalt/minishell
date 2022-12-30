/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sami_norm1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:06:39 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 09:56:13 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

void	pipe_exec(t_cmd *cmd, t_list *list)
{
	t_cmd	*ptr;
	int		fd[2];
	int		status;

	ptr = cmd;
	status = 0;
	while (cmd)
	{
		if (cmd->next)
		{
			pipe(fd);
			cmd->next->tem = fd[0];
		}
		cmd = pipe_exec_norm1(cmd, ptr, fd, list);
		if (!cmd)
			break ;
	}
	pipe_exec_norm(ptr, status);
}

void	change_pwd(t_list *list, char *s)
{
	char	*ptr;

	while (ft_strcmp(list->first, s))
		list = list->next;
	if (!ft_strcmp(list->first, s))
	{
		ptr = getcwd(NULL, 0);
		list->second = ft_strdup(ptr);
		free(ptr);
	}
}

void	ft_cd(t_cmd *cmd, t_list *list)
{
	DIR		*ptr;
	char	*ptr0;

	ptr = NULL;
	ptr0 = NULL;
	if (!cmd->cmd_line[1])
	{
		if (!my_getenv("HOME", list))
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			g_global.g_exit = 1;
			return ;
		}
		ptr = opendir(my_getenv("HOME", list));
		if (ft_cd_norm1(ptr, list))
			return ;
		free(ptr->__dd_buf);
		free(ptr);
		change_pwd(list, "OLDPWD");
		chdir(my_getenv("HOME", list));
	}
	else if (ft_cd_norm(ptr, cmd, list, ptr0))
		return ;
	change_pwd(list, "PWD");
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		write(2, "pwd: .: No such file or directory\n", 34);
		g_global.g_exit = 1;
		return ;
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
}

void	ft_export_uni(t_list *list)
{
	while (list)
	{
		printf("declare -x %s", list->first);
		if (list->sepr == '=')
			printf("=\"%s\"\n", list->second);
		else
			printf("\n");
		list = list->next;
	}
}
