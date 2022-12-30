/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_norm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 02:54:58 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 09:31:49 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/parser.h"

char	*minishell_norm(char *str, t_lexer *lexer, t_line *line, t_list **list)
{
	if (!str)
	{
		printf("exit\n");
		exit(g_global.g_exit_c);
	}
	if (str[0] != 0)
	{
		add_history(str);
		lexer = init_lexer(str);
		line = parser(lexer, *list);
		*list = main_norm(line, *list);
		if (g_global.g_exit != 0)
			g_global.g_exit_c = g_global.g_exit;
	}
	return (str);
}

void	init_minishell(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	g_global.err = 0;
	g_global.g_exit = 0;
	g_global.heredoc = 0;
	g_global.am_red = 0;
	g_global.built = 0;
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
	g_global.g_exit_c = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
