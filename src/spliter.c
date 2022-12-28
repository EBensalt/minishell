/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:54:16 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/27 16:05:52 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	nood_nu(t_line *line)
{
	t_line	*ptr;
	int		i;

	ptr = line;
	i = 0;
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

t_cmd	*new_cmd_nood_norm(t_line *line, t_cmd *cmd)
{
	t_line	*ptr;
	int		i;

	ptr = line;
	i = 0;
	while (ptr && ptr->type != PIPE)
	{
		if (!(ptr->type != SI_RED && ptr->type != SO_RED
				&& ptr->type != DI_RED && ptr->type != DO_RED))
			ptr = ptr->next->next;
		else
		{
			cmd->cmd_line[i] = ft_strdup(ptr->value);
			ptr = ptr->next;
			i++;
		}
	}
	cmd->cmd_line[i] = NULL;
	return (cmd);
}

t_cmd	*new_cmd_nood(t_line *line, t_list *list)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->cmd_line = malloc((nood_nu(line) + 1) * sizeof(char *));
	if ((line->type == SI_RED || line->type == SO_RED || line->type == DI_RED
			|| line->type == DO_RED) && (line->next->next
			&& (line->next->next->type == TEXT
				|| line->next->next->type == S_QUOT
				|| line->next->next->type == D_QUOT
				|| line->next->next->type == ENV_VA)))
		cmd->cmd = ft_strdup(line->next->next->value);
	else if (line->type == TEXT || line->type == S_QUOT || line->type == D_QUOT
		|| line->type == ENV_VA)
		cmd->cmd = ft_strdup(line->value);
	else
		cmd->cmd = NULL;
	cmd = new_cmd_nood_norm(line, cmd);
	cmd->error = cmd_fd(line, cmd, list);
	cmd->next = NULL;
	return (cmd);
}

void	add_cmd_nood(t_cmd **cmd, t_line *line, t_list *list)
{
	t_cmd	*ptr;
	t_cmd	*ptr0;

	ptr = *cmd;
	ptr0 = new_cmd_nood(line, list);
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = ptr0;
}

t_cmd	*spliter(t_line *line, t_list *list)
{
	t_cmd	*cmd;
	t_line	*ptr;

	cmd = NULL;
	if (line)
		cmd = new_cmd_nood(line, list);
	ptr = line;
	while (ptr)
	{
		if (ptr->type == PIPE)
		{
			ptr = ptr->next;
			add_cmd_nood(&cmd, ptr, list);
		}
		ptr = ptr->next;
	}
	return (cmd);
}
