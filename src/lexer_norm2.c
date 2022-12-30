/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_norm2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:04:51 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 09:54:16 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/lexer.h"

char	*my_getenv(char *env, t_list *list)
{
	t_list	*ptr;

	ptr = list;
	while (ptr)
	{
		if (!ft_strcmp(env, ptr->first))
		{
			return (ptr->second);
		}
		ptr = ptr->next;
	}
	return (0);
}

char	*lexer_get_value_norm5(t_lexer *lexer, char *value, t_list *list)
{
	char	*env;

	while (lexer->c == '$' && ft_isalnum_1(lexer->str[lexer->i + 1]) == 1)
	{
		lexer_advance(lexer);
		env = NULL;
		while (ft_isalnum_1(lexer->c) == 1)
		{
			env = ft_strjoin(env, lexer->s_c);
			lexer_advance(lexer);
			if (lexer->c == '/' || lexer->c == '=')
				break ;
		}
		value = ft_strjoin(value, my_getenv(env, list));
	}
	if (lexer->c == '$' && lexer->str[lexer->i + 1] == '?')
	{
		lexer_advance(lexer);
		value = ft_strjoin(value, ft_itoa(g_global.g_exit_c));
		lexer_advance(lexer);
	}
	return (value);
}

char	*lexer_get_value_help(t_lexer *lexer, char *value, t_list *list)
{
	while (ft_isalnum_0(lexer->c) == 1)
	{
		if (ft_isalnum_1(lexer->c) == 1 || lexer->c == '?')
		{
			value = ft_strjoin(value, lexer->s_c);
			lexer_advance(lexer);
		}
		else if (lexer->c == '$' && (lexer->str[lexer->i + 1] == 32
				|| lexer->str[lexer->i + 1] == 9 || !lexer->str[lexer->i + 1]))
		{
			value = ft_strjoin(value, lexer->s_c);
			lexer_advance(lexer);
		}
		else if (lexer->c == '\'')
			value = ft_strjoin(value, lexer_get_value(lexer, S_QUOT, list));
		else if (lexer->c == '"')
			value = ft_strjoin(value, lexer_get_value(lexer, D_QUOT, list));
		else if (lexer->c == '$' && lexer->str[lexer->i + 1] == '?')
			value = ft_strjoin(value, lexer_get_value(lexer, EXIT_C, list));
		else if (lexer->c == '$')
			value = ft_strjoin(value, lexer_get_value(lexer, ENV_VA, list));
	}
	return (value);
}

char	*lexer_get_value_norm7(t_lexer *lexer, char *value, t_list *list)
{
	while (ft_isalnum_0(lexer->c) == 1)
	{
		if (ft_isalnum_1(lexer->c) == 1)
		{
			value = ft_strjoin(value, lexer->s_c);
			lexer_advance(lexer);
		}
		else if (lexer->c == '$' || lexer->c == '?')
		{
			value = ft_strjoin(value, lexer->s_c);
			lexer_advance(lexer);
		}
		else if (lexer->c == '\'')
		{
			value = ft_strjoin(value, lexer_get_value(lexer, S_QUOT, list));
			g_global.heredoc = 1;
		}
		else if (lexer->c == '"')
			value = ft_strjoin(value,
					lexer_get_value(lexer, D_QUOT_HELP, list));
	}
	return (value);
}

char	*lexer_get_value_norm6(int type, t_lexer *lexer,
	char *value, t_list *list)
{
	if (type == D_QUOT_HELP)
	{
		g_global.heredoc = 1;
		lexer_advance(lexer);
		while (lexer->c != '\"')
		{
			if (lexer->c == '\0')
			{
				write(2, "error : all quotes should be closed\n", 36);
				g_global.g_exit = 1;
				return (0);
			}
			value = ft_strjoin(value, lexer->s_c);
			lexer_advance(lexer);
		}
		lexer_advance(lexer);
	}
	if (type == HD_HELP)
	{
		lexer_skip_whitespaces(lexer);
		value = lexer_get_value_norm7(lexer, value, list);
	}
	return (value);
}
