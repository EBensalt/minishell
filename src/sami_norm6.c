/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sami_norm6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 05:36:17 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 13:59:29 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

int	list_checker_norm(t_cmd *cmd, int j, t_list **list)
{
	int		i;

	i = -1;
	while (cmd->cmd_line[j][++i] && cmd->cmd_line[j][i] != '=')
	{
		if (!ft_isalnum_2(cmd->cmd_line[j][i])
			|| (cmd->cmd_line[j][i] == '+'
				&& cmd->cmd_line[j][i + 1] != '='))
		{
			list_checker_norm3(cmd, j);
			j++;
			g_global.g_exit = 1;
		}
		if (!cmd->cmd_line[j])
			return (1);
		else if (cmd->cmd_line[j][i] == '+'
			&& cmd->cmd_line[j][i + 1] == '=')
		{
			g_global.plus = 1;
			break ;
		}
	}
	list_checker_norm1(i, cmd, j, list);
	return (0);
}

void	list_checker_norm1(int i, t_cmd *cmd, int j, t_list **list)
{
	char	*str;
	char	*ptr;

	ptr = my_malloc((i + 1) * sizeof(char));
	ft_strlcpy(ptr, cmd->cmd_line[j], (i + 1));
	if (g_global.plus == 1)
	{
		str = ft_strjoin(my_getenv(ptr, *list),
				&cmd->cmd_line[j][i + 2]);
		delete_env(list, ptr);
		ptr = ft_strjoin(ptr, "=");
		str = ft_strjoin(ptr, str);
		add_list_nood(list, str);
	}
	else if (!env_srch(*list, ptr))
		add_list_nood(list, cmd->cmd_line[j]);
	else
		list_checker_norm2(cmd, i, j, list);
}

int	ft_unset_norm(t_cmd *cmd, int j, t_list **list)
{
	int		i;
	char	*ptr;

	i = -1;
	while (cmd->cmd_line[j][++i])
	{
		if (!ft_isalnum_2(cmd->cmd_line[j][i]) || cmd->cmd_line[j][i] == '+')
		{
			write(2, "minishell: unset: '", 19);
			ft_putstr_fd(cmd->cmd_line[j], 2);
			write(2, "': not a valid identifier\n", 26);
			j++;
			g_global.g_exit = 1;
		}
		if (!cmd->cmd_line[j])
			return (1);
	}
	ptr = my_malloc((i + 1) * sizeof(char));
	ft_strlcpy(ptr, cmd->cmd_line[j], (i + 1));
	if (env_srch(*list, ptr))
		delete_env(list, ptr);
	return (0);
}

void	abdellatif_execution_norm(t_cmd *cmd)
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
}
