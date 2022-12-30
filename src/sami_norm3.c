/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sami_norm3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:10:19 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 10:01:56 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

void	ft_unset(t_cmd *cmd, t_list **list)
{
	int		j;

	j = 0;
	while (cmd->cmd_line[++j])
	{
		if (!ft_isalpha(cmd->cmd_line[j][0]))
		{
			write(2, "minishell: unset: '", 19);
			ft_putstr_fd(cmd->cmd_line[j], 2);
			write(2, "': not a valid identifier\n", 26);
			j++;
			g_global.g_exit = 1;
		}
		if (!cmd->cmd_line[j])
			return ;
		if (ft_unset_norm(cmd, j, list))
			return ;
	}
}

void	ft_env(t_list *list)
{
	while (list)
	{
		if (list->sepr == '=')
			printf("%s=%s\n", list->first, list->second);
		list = list->next;
	}
}

int	check_built(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmd, "echo") || !ft_strcmp(cmd->cmd, "cd")
		|| !ft_strcmp(cmd->cmd, "pwd") || !ft_strcmp(cmd->cmd, "export")
		|| !ft_strcmp(cmd->cmd, "unset") || !ft_strcmp(cmd->cmd, "env")
		|| !ft_strcmp(cmd->cmd, "exit"))
		return (0);
	else
		g_global.built = 1;
	return (1);
}

t_list	*builtins_exec(t_cmd *cmd, t_list *list)
{
	int	i;

	i = 0;
	if (!ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd->cmd_line);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		ft_cd(cmd, list);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->cmd, "export"))
		ft_export(cmd, list);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		ft_unset(cmd, &list);
	else if (!ft_strcmp(cmd->cmd, "env"))
		ft_env(list);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		ft_exit(cmd->cmd_line);
	else
		g_global.built = 1;
	return (list);
}

t_list	*abdellatif_execution(t_cmd *cmd, t_list *list)
{
	int		tmp0;
	int		tmp1;

	if (cmd->next)
		pipe_exec(cmd, list);
	if (!check_built(cmd))
	{
		tmp0 = dup(0);
		tmp1 = dup(1);
		abdellatif_execution_norm(cmd);
		list = builtins_exec(cmd, list);
		dup2(tmp0, 0);
		close(tmp0);
		dup2(tmp1, 1);
		close(tmp1);
	}
	if (g_global.built == 1)
		pipe_exec(cmd, list);
	return (list);
}
