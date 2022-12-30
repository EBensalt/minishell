/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:43:21 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 15:16:36 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/parser.h"

void	ft_close(t_cmd *cmd)
{
	t_cmd	*ptr;

	ptr = cmd;
	while (ptr)
	{
		if (ptr->fd_i != 0)
			close(ptr->fd_i);
		if (ptr->fd_o != 1)
			close(ptr->fd_o);
		ptr = ptr->next;
	}
}

t_list	*main_norm(t_line *line, t_list *list)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (g_global.g_exit == 0)
	{
		if (checker(line) == 0)
		{
			cmd = spliter(line, list);
			if (cmd && cmd->cmd && !g_global.err)
				list = abdellatif_execution(cmd, list);
			ft_close(cmd);
			g_global.g_exit_c = 0;
		}
	}
	return (list);
}

char	*first_node(char *tmp, int type)
{
	int		i;
	char	*str;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '=')
		{
			if (type == 1)
				str = ft_substr(tmp, 0, i);
			else
				str = ft_substr(tmp, i + 1, ft_strlen(tmp) - (i + 1));
			return (str);
		}
		i++;
	}
	if (type == 1)
		return (tmp);
	else
		return (NULL);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_lexer	*lexer;
	t_line	*line;
	t_list	*list;

	(void)argc;
	(void)argv;
	g_global.g_exit_c = 0;
	g_global.count = 0;
	list = init_env(env);
	list->original = list;
	lexer = NULL;
	line = NULL;
	while (1)
	{
		init_minishell();
		str = readline("Minishell$ ");
		str = minishell_norm(str, lexer, line, &list);
		if (!str[0])
			free(str);
	}
}
