/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_norm1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:14:29 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/28 10:56:15 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/parser.h"

t_token	*lexer_get_next_token_norm(t_lexer *lexer, t_list *list)
{
	if (lexer->c == '>')
	{
		if (lexer->str[lexer->i + 1] == '>')
			return (init_token(lexer_get_value(lexer, DO_RED, list), DO_RED));
		return (init_token(lexer_get_value(lexer, SO_RED, list), SO_RED));
	}
	if (lexer->c == '|')
		return (init_token(lexer_get_value(lexer, PIPE, list), PIPE));
	if (lexer->c == '$')
	{
		if (lexer->str[lexer->i + 1] == '?')
			return (init_token(lexer_get_value(lexer, EXIT_C, list), EXIT_C));
		if (ft_isalnum_0(lexer->str[lexer->i + 1]) == 1)
			return (init_token(lexer_get_value(lexer, ENV_VA, list), ENV_VA));
		else
			return (init_token(lexer_get_value(lexer, TEXT, list), TEXT));
	}
	if (ft_isalnum_0(lexer->c) == 1)
		return (init_token(lexer_get_value(lexer, TEXT, list), TEXT));
	return (0);
}

t_token	*lexer_get_next_token(t_lexer *lexer, t_list *list)
{
	t_token	*token;

	while (lexer->c != '\0')
	{
		lexer_skip_whitespaces(lexer);
		if ((lexer->c == '\'' && lexer->str[lexer->i + 1] == '\'')
			|| (lexer->c == '"' && lexer->str[lexer->i + 1] == '"'))
		{
			lexer_advance(lexer);
			lexer_advance(lexer);
		}
		if (lexer->c == '\'')
			return (init_token(lexer_get_value(lexer, S_QUOT, list), S_QUOT));
		if (lexer->c == '"')
			return (init_token(lexer_get_value(lexer, D_QUOT, list), D_QUOT));
		if (lexer->c == '<')
		{
			if (lexer->str[lexer->i + 1] == '<')
				return (init_token(lexer_get_value(lexer, DI_RED, list),
						DI_RED));
			return (init_token(lexer_get_value(lexer, SI_RED, list), SI_RED));
		}
		token = lexer_get_next_token_norm(lexer, list);
		if (token)
			return (token);
		lexer_advance(lexer);
	}
	return (0);
}

char	*lexer_get_value_norm4(t_lexer *lexer, int type,
char *value, t_list *list)
{
	if (type == D_QUOT)
	{
		lexer_advance(lexer);
		while (lexer->c != '"')
		{
			if (lexer->c == '\0')
			{
				printf("error : all quotes should be closed\n");
				g_exit = 1;
				return (0);
			}
			value = lexer_get_value_norm5(lexer, value, list);
			if (lexer->c == '"')
				break ;
			value = ft_strjoin(value, lexer->s_c);
			lexer_advance(lexer);
		}
		lexer_advance(lexer);
		value = lexer_get_value_help(lexer, value, list);
	}
	return (value);
}

char	*lexer_get_value_norm3(t_lexer *lexer, int type,
char *value, t_list *list)
{
	value = lexer_get_value_norm4(lexer, type, value, list);
	if (type == SI_RED || type == SO_RED || type == DI_RED || type == DO_RED
		|| type == PIPE)
	{
		value = ft_strjoin(value, lexer->s_c);
		lexer_advance(lexer);
		if (type == DI_RED || type == DO_RED)
		{
			value = ft_strjoin(value, lexer->s_c);
			lexer_advance(lexer);
		}
	}
	return (value);
}

char	*lexer_get_value_norm2(t_lexer *lexer, int type,
char *value, t_list *list)
{
	char	*env;

	value = lexer_get_value_norm3(lexer, type, value, list);
	if (type == ENV_VA)
	{
		if (lexer->c == '$' && ft_isalnum_1(lexer->str[lexer->i + 1]) == 0)
			lexer_advance(lexer);
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
			// free(env);
		}
		value = lexer_get_value_help(lexer, value, list);
	}
	return (value);
}
