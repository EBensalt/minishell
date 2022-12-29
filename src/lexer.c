/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:36:45 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/29 09:03:23 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/parser.h"

t_lexer	*init_lexer(char *str)
{
	t_lexer	*lexer;

	lexer = my_malloc(sizeof(t_lexer));
	lexer->str = str;
	lexer->i = 0;
	lexer->c = str[lexer->i];
	lexer->s_c = my_malloc(2 * sizeof(char));
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
		value = lexer_get_value_help(lexer, value, list);
	}
	if (type == TEXT)
	{
		value = lexer_get_value_help(lexer, value, list);
		// while (ft_isalnum_0(lexer->c) == 1)
		// {
		// 	if (lexer->c == '\'')
		// 		value = ft_strjoin(value, lexer_get_value(lexer, S_QUOT, list));
		// 	else if (lexer->c == '"')
		// 		value = ft_strjoin(value, lexer_get_value(lexer, D_QUOT, list));
		// 	else if (lexer->c == '$' && lexer->str[lexer->i + 1] == '?')
		// 		value = ft_strjoin(value, lexer_get_value(lexer, EXIT_C, list));
		// 	else if (lexer->c == '$')
		// 		value = ft_strjoin(value, lexer_get_value(lexer, ENV_VA, list));
		// 	else if (ft_isalnum_1(lexer->c) == 1)
		// 	{
		// 		value = ft_strjoin(value, lexer->s_c);
		// 		lexer_advance(lexer);
		// 	}
		// }
	}
	if (type == D_QUOT_HELP)
	{
		heredoc = 1;
		lexer_advance(lexer);
		while (lexer->c != '\"')
		{
			if (lexer->c == '\0')
			{
				printf("error : all quotes should be closed\n");
				g_exit = 1;
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
				heredoc = 1;
			}
			else if (lexer->c == '"')
				value = ft_strjoin(value, lexer_get_value(lexer, D_QUOT_HELP, list));
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
				printf("error : all quotes should be closed\n");
				g_exit = 1;
				return (0);
			}
			value = ft_strjoin(value, lexer->s_c);
			lexer_advance(lexer);
		}
		lexer_advance(lexer);
		value = lexer_get_value_help(lexer, value, list);
	}
	value = lexer_get_value_norm1(lexer, type, value, list);
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
		// else if (lexer->c == '$' && (ft_isalnum_1(lexer->str[lexer->i + 1]) == 0 || !lexer->str[lexer->i + 1]))
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