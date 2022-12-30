/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 03:27:24 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 03:12:29 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_line	*new_nood(t_token *token)
{
	t_line	*nood;

	nood = my_malloc(sizeof(t_line));
	nood->value = ft_strdup(token->value);
	nood->type = token->e_type;
	nood->next = NULL;
	return (nood);
}

void	add_nood(t_line **line, t_token *token)
{
	t_line	*ptr;
	t_line	*ptr0;

	ptr = *line;
	ptr0 = new_nood(token);
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = ptr0;
}

void	print_nood(t_line *line)
{
	t_line	*ptr;

	ptr = line;
	while (ptr)
	{
		printf("(%s, %d)\n", ptr->value, ptr->type);
		ptr = ptr->next;
	}
}

int	check_space(t_token *token)
{
	int	i;

	i = -1;
	while (token->value && token->value[++i])
	{
		if ((token->value[i] == 9 || token->value[i] == 32)
			&& token->value[i + 1])
			return (1);
	}
	return (0);
}

t_line	*parser(t_lexer *lexer, t_list *list)
{
	t_token	*token;
	t_line	*line;

	line = NULL;
	while (lexer->c != '\0')
	{
		token = lexer_get_next_token(lexer, list);
		if (!token)
			break ;
		line = parser_norm1(token, line);
		if (token->e_type == DI_RED)
		{
			token = init_token(lexer_get_value(lexer, HD_HELP, list), HD_HELP);
			if (!token)
				break ;
			line = parser_norm1(token, line);
		}
	}
	return (line);
}
