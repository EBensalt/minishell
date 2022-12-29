/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 03:27:20 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/15 16:16:04 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# include "token.h"
# include "minishell.h"

typedef struct s_line
{
	char			*value;
	int				type;
	int				am_red;
	struct s_line	*next;
}	t_line;
typedef struct s_cmd
{
	char			*cmd;
	char			**cmd_line;
	int				fd_i;
	int				fd_o;
	int				error;
	struct s_cmd	*next;
}	t_cmd;

t_line	*parser(t_lexer *lexer);
int		checker(t_line *line);
t_cmd	*spliter(t_line *line);
void	print_nood(t_line *line);
int		cmd_fd(t_line *line, t_cmd *cmd);
t_line	*parser_norm1(t_token *token, t_line *line);
t_line	*new_nood(t_token *token);
void	add_nood(t_line **line, t_token *token);
int		check_space(t_token *token);
#endif