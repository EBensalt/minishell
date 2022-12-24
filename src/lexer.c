/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:36:45 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/23 18:10:46 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/parser.h"

t_lexer	*init_lexer(char *str)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->str = str;
	lexer->i = 0;
	lexer->c = str[lexer->i];
	lexer->s_c = malloc(2 * sizeof(char));
	lexer->s_c[0] = lexer->c;
	lexer->s_c[1] = '\0';
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0')
	{
		lexer->i++;
		lexer->c = lexer->str[lexer->i];
		lexer->s_c[0] = lexer->c;
		lexer->s_c[1] = '\0';
	}
}

void	lexer_skip_whitespaces(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t')
		lexer_advance(lexer);
}

char	*lexer_get_value_norm1(t_lexer *lexer, int type,
			char *value, t_list *list)
{
	value = lexer_get_value_norm2(lexer, type, value, list);
	if (type == EXIT_C)
	{
		lexer_advance(lexer);
		value = ft_strjoin(value, ft_itoa(g_exit_c));
		lexer_advance(lexer);
	}
	if (type == TEXT)
	{
		if (lexer->c == '$')
		{
			value = ft_strjoin(value, lexer->s_c);
			lexer_advance(lexer);
		}
		while (ft_isalnum_0(lexer->c) == 1)
		{
			if (lexer->c == '\'')
				value = ft_strjoin(value, lexer_get_value(lexer, S_QUOT, list));
			if (lexer->c == '"')
				value = ft_strjoin(value, lexer_get_value(lexer, D_QUOT, list));
			if (lexer->c == '$')
				value = ft_strjoin(value, lexer_get_value(lexer, ENV_VA, list));
			if (ft_isalnum_1(lexer->c) == 1)
			{
				value = ft_strjoin(value, lexer->s_c);
				lexer_advance(lexer);
			}
		}
	}
	return (value);
}

char	*lexer_get_value(t_lexer *lexer, int type, t_list *list)
{
	char	*value;

	value = NULL;
	if (type == S_QUOT)
	{
		lexer_advance(lexer);
		while (lexer->c != '\'')
		{
			if (lexer->c == '\0')
			{
				printf("\033[0;31merror\033[0m : all quotes should be closed\n");
				g_exit = 1;
				return (0);
			}
			value = ft_strjoin(value, lexer->s_c);
			lexer_advance(lexer);
		}
		lexer_advance(lexer);
	}
	value = lexer_get_value_norm1(lexer, type, value, list);
	return (value);
}
