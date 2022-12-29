/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:40:40 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/16 14:39:26 by ebensalt         ###   ########.fr       */
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

int	g_exit;
int	g_exit_c;

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int		ft_isalnum(int c);
int		ft_isalnum_0(int c);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
#endif