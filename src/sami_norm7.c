/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sami_norm7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 08:49:17 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 10:32:54 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

void	list_checker_norm2(t_cmd *cmd, int i, int j, t_list **list)
{
	char	*ptr;
	char	*str;

	ptr = my_malloc((i + 1) * sizeof(char));
	ft_strlcpy(ptr, cmd->cmd_line[j], (i + 1));
	str = my_getenv(ptr, *list);
	if (!str || (!cmd->cmd_line[j][i + 1] && cmd->cmd_line[j][i] == '=')
		|| (cmd->cmd_line[j][i + 1] != 0
			&& ft_strcmp(str, &cmd->cmd_line[j][i + 1])))
	{
		delete_env(list, ptr);
		add_list_nood(list, cmd->cmd_line[j]);
	}
}

void	list_checker_norm3(t_cmd *cmd, int j)
{
	write(2, "minishell: export: '", 20);
	ft_putstr_fd(cmd->cmd_line[j], 2);
	write(2, "': not a valid identifier\n", 26);
}

void	cmd_fd_norm9(t_line *ptr)
{
	if (ptr)
	{
		write(2, "error : ", 8);
		ft_putstr_fd(ptr->next->value, 2);
		write(2, " Is directory\n", 14);
	}
	else
	{
		write(2, "error : ", 8);
		ft_putstr_fd(ptr->next->value, 2);
		write(2, " no such file or directory\n", 27);
	}
}
