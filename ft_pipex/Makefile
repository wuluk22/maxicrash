# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clegros <clegros@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 11:07:51 by clegros           #+#    #+#              #
#    Updated: 2024/02/07 11:07:53 by clegros          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MSRC = child_mgmt.c free.c parsing.c pipex.c error.c\
	ft_split.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_putstr_fd.c

MOBJ = ${MSRC:.c=.o}

all : $(NAME)

$(NAME): $(MOBJ) pipex.h
	@ar rc $(NAME) $(MOBJ)

%.o: %.c pipex.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(MOBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all