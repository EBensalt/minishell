/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_norm1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:14:29 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/15 16:18:30 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"

t_token	*lexer_get_next_token_norm(t_lexer *lexer)
{
	if (lexer->c == '>')
	{
		if (lexer->str[lexer->i + 1] == '>')
			return (init_token(lexer_get_value(lexer, DO_RED), DO_RED));
		return (init_token(lexer_get_value(lexer, SO_RED), SO_RED));
	}
	if (lexer->c == '|')
		return (init_token(lexer_get_value(lexer, PIPE), PIPE));
	if (lexer->c == '$')
	{
		if (lexer->str[lexer->i + 1] == '?')
			return (init_token(lexer_get_value(lexer, EXIT_C), EXIT_C));
		if (ft_isalnum_0(lexer->str[lexer->i + 1]) == 1)
			return (init_token(lexer_get_value(lexer, ENV_VA), ENV_VA));
		else
			return (init_token(lexer_get_value(lexer, TEXT), TEXT));
		printf("ok\n");
	}
	if (ft_isalnum_0(lexer->c) == 1)
		return (init_token(lexer_get_value(lexer, TEXT), TEXT));
	return (0);
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	t_token	*token;

	while (lexer->c != '\0')
	{
		lexer_skip_whitespaces(lexer);
		if (lexer->c == '\'')
			return (init_token(lexer_get_value(lexer, S_QUOT), S_QUOT));
		if (lexer->c == '"')
			return (init_token(lexer_get_value(lexer, D_QUOT), D_QUOT));
		if (lexer->c == '<')
		{
			if (lexer->str[lexer->i + 1] == '<')
				return (init_token(lexer_get_value(lexer, DI_RED), DI_RED));
			return (init_token(lexer_get_value(lexer, SI_RED), SI_RED));
		}
		token = lexer_get_next_token_norm(lexer);
		if (token)
			return (token);
		lexer_advance(lexer);
	}
	return (0);
}

char	*lexer_get_value_norm4(t_lexer *lexer, int type, char *value)
{
	if (type == D_QUOT)
	{
		lexer_advance(lexer);
		while (lexer->c != '"')
		{
			if (lexer->c == '\0')
			{
				printf("\033[0;31merror\033[0m : all quotes should be closed\n");
				g_exit = 2;
				return (0);
			}
			value = lexer_get_value_norm5(lexer, value);
			if (lexer->c == '"')
				break ;
			value = ft_strjoin(value, lexer->s_c);
			lexer_advance(lexer);
		}
		lexer_advance(lexer);
	}
	return (value);
}

char	*lexer_get_value_norm3(t_lexer *lexer, int type, char *value)
{
	value = lexer_get_value_norm4(lexer, type, value);
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

char	*lexer_get_value_norm2(t_lexer *lexer, int type, char *value)
{
	char	*env;

	value = lexer_get_value_norm3(lexer, type, value);
	if (type == ENV_VA)
	{
		while (lexer->c == '$' && ft_isalnum_0(lexer->str[lexer->i + 1]) == 1)
		{
			lexer_advance(lexer);
			env = NULL;
			while (ft_isalnum_0(lexer->c) == 1)
			{
				env = ft_strjoin(env, lexer->s_c);
				lexer_advance(lexer);
			}
			value = ft_strjoin(value, getenv(env));
			free(env);
		}
	}
	return (value);
}
