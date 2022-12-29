/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:31:09 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/12 22:17:19 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "token.h"

typedef struct s_lexer
{
	char	*str;
	char	c;
	char	*s_c;
	int		i;
}	t_lexer;

t_lexer	*init_lexer(char *str);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespaces(t_lexer *lexer);
t_token	*lexer_get_next_token(t_lexer *lexer);
char	*lexer_get_value(t_lexer *lexer, int type);
char	*lexer_get_value_norm2(t_lexer *lexer, int type, char *value);
char	*lexer_get_value_norm5(t_lexer *lexer, char *value);
void	lexer_advance_all(t_lexer *lexer);
#endif