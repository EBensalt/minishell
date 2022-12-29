# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/23 16:08:05 by ebensalt          #+#    #+#              #
#    Updated: 2022/12/16 14:38:46 by ebensalt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
C = src/minishell.c \
	src/lexer.c \
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
	src/ft_strlen.c
O = $(C:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
all : $(NAME)
$(NAME) : $(O)
	$(CC) $(CFLAGS) $(O) -o $(NAME) -lreadline
	clear
clean :
	rm -rf */*.o
	clear
fclean : clean
	rm -rf $(NAME)
	clear
re : fclean all