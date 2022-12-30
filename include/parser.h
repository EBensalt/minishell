/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 03:27:20 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 15:22:40 by ebensalt         ###   ########.fr       */
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
	struct s_line	*next;
}	t_line;
typedef struct s_cmd
{
	char			*cmd;
	char			**cmd_line;
	int				fd_i;
	int				fd_o;
	int				tem;
	int				error;
	int				id;
	struct s_cmd	*next;
}	t_cmd;
typedef struct s_list
{
	char			*first;
	char			*second;
	char			sepr;
	struct s_list	*original;
	struct s_list	*next;
}	t_list;

t_token		*lexer_get_next_token(t_lexer *lexer, t_list *list);
char		*lexer_get_value(t_lexer *lexer, int type, t_list *list);
char		*lexer_get_value_norm2(t_lexer *lexer, int type,
				char *value, t_list *list);
char		*lexer_get_value_norm5(t_lexer *lexer, char *value, t_list *list);
t_list		*new_list(char *tmp);
t_line		*parser(t_lexer *lexer, t_list *list);
int			checker(t_line *line);
t_cmd		*spliter(t_line *line, t_list *list);
void		print_nood(t_line *line);
int			cmd_fd(t_line *line, t_cmd *cmd, t_list *list);
t_line		*parser_norm1(t_token *token, t_line *line);
t_line		*new_nood(t_token *token);
void		add_nood(t_line **line, t_token *token);
int			check_space(t_token *token);
t_list		*abdellatif_execution(t_cmd *cmd, t_list *list);
char		*my_getenv(char *env, t_list *list);
int			search_commande(t_list *list, char *commande, char **argv);
void		ft_mini_help_ft_trait(char **argv, t_list *list, char *commande);
char		**my_magic(t_list *list);
char		*ft_strchr(const char *s, int c);
t_list		*builtins_exec(t_cmd *cmd, t_list *list);
char		**ft_split_exec(char const *s, char c);
char		*lexer_get_value_help(t_lexer *lexer, char *value, t_list *list);
long long	ft_atoi(const char *nptr);
int			ft_isalpha(int c);
int			ft_isalnum_2(int c);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*lexer_get_value_norm6(int type, t_lexer *lexer,
				char *value, t_list *list);
t_list		*init_env(char **env);
void		handler(int i);
t_list		*new_list(char *tmp);
void		init_minishell(void);
char		*minishell_norm(char *str, t_lexer *lexer,
				t_line *line, t_list **list);
t_list		*main_norm(t_line *line, t_list *list);
void		ft_echo(char **str);
int			ft_exit(char **args);
void		is_numeric(char **args);
int			count_args(char **args);
int			check_opt(char *str);
void		my_execve(t_cmd *cmd, t_list *list);
void		handler0(int i);
void		ft_export_uni(t_list *list);
int			env_srch(t_list *list, char *str);
void		delete_env(t_list **list, char *str);
void		ft_cd(t_cmd *cmd, t_list *list);
void		ft_pwd(void);
void		ft_export(t_cmd *cmd, t_list *list);
void		pipe_exec(t_cmd *cmd, t_list *list);
t_cmd		*command_creation_norm(t_cmd *cmd, char *str, int i);
void		my_execve_norm(t_cmd *cmd, t_list *list, char **env);
t_cmd		*command_creation(t_cmd *cmd, t_list *list);
char		**env_creat(t_list *list);
void		ft_echo_norm(char **str, int i);
void		pipe_exec_norm(t_cmd *ptr, int status);
t_cmd		*pipe_exec_norm1(t_cmd *cmd, t_cmd *ptr, int fd[2], t_list *list);
t_cmd		*pipe_exec_norm2(t_cmd *cmd, t_cmd *ptr, int fd[2]);
void		pipe_exec_norm3(t_cmd *cmd, t_cmd *ptr, int fd[2], t_list *list);
int			ft_cd_norm(DIR *ptr, t_cmd *cmd, t_list *list, char *ptr0);
int			ft_cd_norm1(DIR *ptr, t_list *list);
void		change_pwd(t_list *list, char *s);
void		delete_env_norm(t_list *ptr, t_list *ptr0);
int			list_checker_norm(t_cmd *cmd, int j, t_list **list);
void		list_checker_norm1(int i, t_cmd *cmd, int j, t_list **list);
void		add_list_nood(t_list **list, char *new);
int			ft_unset_norm(t_cmd *cmd, int j, t_list **list);
void		abdellatif_execution_norm(t_cmd *cmd);
void		list_checker_norm2(t_cmd *cmd, int i, int j, t_list **list);
void		handler_herdock(int i);
void		cmd_fd_norm4(t_line *ptr, int fd, t_list *list);
int			cmd_fd_norm1(t_cmd *cmd, t_line *ptr);
void		cmd_fd_norm6(t_line *ptr);
int			cmd_fd_norm7(char *str, int fd, t_list *list);
int			cmd_fd_norm8(char *str, int i, t_list *list, int fd);
char		*cmd_fd_norm5(char *str, int i, t_list *list);
void		list_checker_norm3(t_cmd *cmd, int j);
void		cmd_fd_norm9(t_line *ptr, DIR *ptr0);

#endif