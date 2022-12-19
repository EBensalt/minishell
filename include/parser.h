/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 03:27:20 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/18 22:54:23 by ebensalt         ###   ########.fr       */
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
typedef struct s_list
{
	char			*first;
	char			*second;
	struct s_list	*original;
	struct s_list	*next;
}	t_list;

t_token	*lexer_get_next_token(t_lexer *lexer, t_list *list);
char	*lexer_get_value(t_lexer *lexer, int type, t_list *list);
char	*lexer_get_value_norm2(t_lexer *lexer, int type,
			char *value, t_list *list);
char	*lexer_get_value_norm5(t_lexer *lexer, char *value, t_list *list);
t_list	*new_list(char *tmp);
t_line	*parser(t_lexer *lexer, t_list *list);
int		checker(t_line *line);
t_cmd	*spliter(t_line *line);
void	print_nood(t_line *line);
int		cmd_fd(t_line *line, t_cmd *cmd);
t_line	*parser_norm1(t_token *token, t_line *line);
t_line	*new_nood(t_token *token);
void	add_nood(t_line **line, t_token *token);
int		check_space(t_token *token);
t_list	*abdellatif_execution(t_cmd *cmd, t_list *list, char **env);
char	*my_getenv(char *env, t_list *list);

#endif