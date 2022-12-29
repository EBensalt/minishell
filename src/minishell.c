/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:43:21 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/29 13:26:04 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include <stdio.h>

void	my_free_norm(t_cmd *cmd)
{
	t_cmd	*ptr;
	int		i;

	ptr = cmd;
	while (ptr)
	{
		ptr = ptr->next;
		if (cmd->cmd)
			free(cmd->cmd);
		i = -1;
		while (cmd->cmd_line[++i])
			free(cmd->cmd_line[i]);
		if (cmd->cmd_line)
			free(cmd->cmd_line);
		free(cmd);
		cmd = ptr;
	}
}

// void	my_free(t_cmd *cmd, t_line *line)
// {
// 	t_line	*ptr0;

// 	ptr0 = line;
// 	while (ptr0)
// 	{
// 		ptr0 = ptr0->next;
// 		// free(line->value);
// 		// free(line);
// 		line = ptr0;
// 	}
// 	my_free_norm(cmd);
// }

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

t_list	*main_norm(t_line *line, t_list *list, char **env)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (g_exit == 0)
	{
		if (checker(line) == 0)
		{
			cmd = spliter(line, list);
			// while (cmd)
			// {
			// 	int	i = -1;
			// 	while (line)
			// 	{
			// 		printf("%s\n", cmd->cmd_line[++i]);
			// 		line = line->next;
			// 	}
			// 	cmd = cmd->next;
			// }
			// exit(0);
			if (cmd && cmd->cmd && !err)
			{
				list = abdellatif_execution(cmd, list, env);
			}
			ft_close(cmd);
			g_exit_c = 0;
			// my_free(cmd, line);
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

t_list	*new_list(char *tmp)
{
	t_list	*listnew;

	listnew = malloc(sizeof(t_list));
	listnew->first = first_node(tmp, 1);
	if (ft_strcmp(listnew->first, tmp))
		listnew->sepr = '=';
	listnew->second = first_node(tmp, 2);
	listnew->next = NULL;
	return (listnew);
}

t_list	*init_env(char **env)
{
	t_list	*list;
	t_list	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		if (i == 0)
		{
			list = new_list(env[i]);
			tmp = list;
		}
		else
		{
			tmp->next = new_list(env[i]);
			tmp = tmp->next;
		}
		i++;
	}
	return (list);
}

void	handler(int i)
{
	(void)i;
	g_exit_c = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_lexer	*lexer;
	t_line	*line;
	t_list	*list;

	(void)argc;
	(void)argv;
	g_exit_c = 0;
	count = 0;
	list = init_env(env);
	// while (list)
	// {
	// 	printf("%s%c%s\n", list->first, list->sepr, list->second);
	// 	list = list->next;
	// }
	// exit(0);
	list->original = list;
	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		err = 0;
		g_exit = 0;
		heredoc = 0;
		am_red = 0;
		built = 0;
		str = readline("Minishell$ ");
		if (!str)
		{
			printf("exit\n");
			exit(g_exit_c);
		}
		if (str[0] != 0)
		{
			add_history(str);
			lexer = init_lexer(str);
			line = parser(lexer, list);
			// while (line)
			// {
			// 	printf("%s\n", line->value);
			// 	line = line->next;
			// }
			// exit(0);
			list = main_norm(line, list, env);
		// while (list)
		// 		{
		// 			printf("declare -x %s\n", (list)->first);
		// 			// if (*list->sepr == '=')
		// 			// 	printf("=\"%s\"\n", list->second);
		// 			// else
		// 			// 	printf("\n");
		// 			list = (list)->next;
		// 		}
		// 		exit(0);
			if (g_exit != 0)
				g_exit_c = g_exit;
			// free(lexer->s_c);
			// free(lexer);
			// free(str);
		}
		if (!str[0])
			free(str);
		// my_free();
		// system("leaks minishell");
	}
}

// int	main(void)
// {
// 	char	*str;
// 	t_lexer	*lexer;
// 	t_line	*line;
// 	t_cmd	*cmd;
// 	t_cmd	*ptr;
// 	int		i;

// 	g_exit_c = 0;
// 	while (1)
// 	{
// 		g_exit = 0;
// 		str = readline("\033[1;33mMinishell \033[0m");
// 		if (str[0] != 0)
// 		{
// 			add_history(str);
// 			if (str[0] == 'q' && str[1] == '\0')
// 				exit(0);
// 			lexer = init_lexer(str);
// 			line = parser(lexer);
// 			cmd = main_norm(line);
// 			ptr = cmd;
// 			while (ptr && g_exit == 0)
// 			{
// 				printf("cmd : %s\n", ptr->cmd);
// 				i = -1;
// 				while (ptr->cmd_line[++i])
// 					printf("cmd->line %d : %s\n", (i + 1), ptr->cmd_line[i]);
// 				printf("cmd->red : %d, %d\n", ptr->fd_i, ptr->fd_o);
// 				ptr = ptr->next;
// 			}
// 			if (g_exit != 0)
// 				g_exit_c = g_exit;
// 			free(lexer->s_c);
// 			free(lexer);
// 		}
// 		free(str);
// 		// system("leaks minishell");
// 	}
// }
