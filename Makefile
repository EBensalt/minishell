# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/23 16:08:05 by ebensalt          #+#    #+#              #
#    Updated: 2022/12/29 09:12:22 by ebensalt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
C = src/minishell.c \
	src/lexer.c \
	src/ft_substr.c\
	src/sami.c\
	src/ft_putstr_fd.c\
	src/lexer_norm1.c \
	src/lexer_norm2.c \
	src/token.c \
	src/ft_strjoin.c \
	src/ft_strdup.c \
	src/ft_isalnum.c \
	src/parser.c \
	src/parser_norm.c \
	src/checker.c \
	src/spliter.c \
	src/spliter_norm.c \
	src/ft_split.c \
	src/ft_itoa.c \
	src/ft_strcmp.c \
	src/ft_strlen.c \
	src/system.c \
	src/help_sami.c \
	src/ft_strchr.c \
	src/ft_split_exec.c \
	src/ft_atoi.c \
	src/ft_isalpha.c \
	src/ft_strlcpy.c \
	src/my_malloc.c
O = $(C:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -I/goinfre/ebensalt/homebrew/opt/readline/include 
READLINE =  -lreadline -L/goinfre/ebensalt/homebrew/opt/readline/lib
all : $(NAME)
$(NAME) : $(O)
	$(CC) $(CFLAGS) $(O) -o $(NAME) $(READLINE)
	clear
clean :
	rm -rf */*.o
	clear
fclean : clean
	rm -rf $(NAME)
	clear
re : fclean all
