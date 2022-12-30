/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sami_norm2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:08:29 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 09:59:21 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

void	add_list_nood(t_list **list, char *new)
{
	t_list	*ptr;
	t_list	*ptr0;

	ptr = *list;
	ptr0 = new_list(new);
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = ptr0;
}

void	delete_env(t_list **list, char *str)
{
	t_list	*ptr;
	t_list	*ptr0;

	ptr = *list;
	while (ptr)
	{
		if (!ft_strcmp(ptr->first, str))
		{
			if (ptr == *list)
			{
				*list = (*list)->next;
				free(ptr);
				return ;
			}
			else
				delete_env_norm(ptr, ptr0);
		}
		ptr0 = ptr;
		ptr = ptr->next;
	}
}

int	env_srch(t_list *list, char *str)
{
	while (list)
	{
		if (!ft_strcmp(list->first, str))
			return (1);
		list = list->next;
	}
	return (0);
}

void	list_checker(t_cmd *cmd, t_list **list)
{
	int		j;
	int		plus;

	j = 0;
	plus = 0;
	while (cmd->cmd_line[++j])
	{
		if (!ft_isalpha(cmd->cmd_line[j][0]))
		{
			write(2, "minishell: export: '", 20);
			ft_putstr_fd(cmd->cmd_line[j], 2);
			write(2, "': not a valid identifier\n", 26);
			j++;
			g_global.g_exit = 1;
		}
		if (!cmd->cmd_line[j])
			return ;
		if (list_checker_norm(cmd, j, list))
			return ;
	}
}

void	ft_export(t_cmd *cmd, t_list *list)
{
	if (!cmd->cmd_line[1])
		ft_export_uni(list);
	else
		list_checker(cmd, &list);
}
