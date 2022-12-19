/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_norm2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:04:51 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/18 22:28:01 by ebensalt         ###   ########.fr       */
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
			return (ptr->second);
		ptr = ptr->next;
	}
	return (0);
}

char	*lexer_get_value_norm5(t_lexer *lexer, char *value, t_list *list)
{
	char	*env;

	while (lexer->c == '$' && ft_isalnum(lexer->str[lexer->i + 1]) == 1)
	{
		lexer_advance(lexer);
		env = NULL;
		while (ft_isalnum(lexer->c) == 1)
		{
			env = ft_strjoin(env, lexer->s_c);
			lexer_advance(lexer);
		}
		value = ft_strjoin(value, my_getenv(env, list));
		free(env);
	}
	return (value);
}
