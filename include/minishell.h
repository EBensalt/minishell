/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:40:40 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/24 17:10:56 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>

int	g_exit;
int	g_exit_c;
int	err;

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int		ft_isalnum(int c);
int		ft_isalnum_0(int c);
int		ft_isalnum_1(int c);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putstr_fd(char *s, int fd);
char	*first_node(char *tmp, int type);

#endif