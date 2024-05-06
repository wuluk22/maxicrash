# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 16:52:09 by clegros           #+#    #+#              #
#    Updated: 2024/04/10 14:10:47 by yohanafi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN=\033[0;32m
YELLOW=\033[0;33m
NC=\033[0m

define PRINT_LOADING_BAR
	@progress=$$(echo "scale=2; $(1) / $(2) * 100" | bc); \
	percentage=$$(printf "%.0f" $$progress); \
	echo "Progress: [$$percentage%]"
endef

NAME    = minishell
SRC     = minishell.c\
            ft_lexer.c\
            ft_free.c\
			ft_lstadd_back.c\
			ft_lstlast.c\
			ft_lstnew.c\
			ft_signals.c\
			ft_str_utils.c\
			lexer.c\
			ft_exec.c\
			ft_append.c\
			ft_heredoc.c\
			ft_input_red.c\
			ft_redirect.c\
			ft_str_utils_s.c	
OBJ     = $(SRC:.c=.o)
CC      = gcc
CFLAGS  = -Wall -Werror -Wextra
COMP    = $(CC) $(CFLAGS)
RM      = rm -f
DIR_INC = -Ift_pipex/
PIP_LIB = ft_pipex/pipex.a
RDL_PAT = $(shell brew --prefix readline)
RDL_LIB = -lreadline -lhistory -L $(RDL_PAT)/lib
RDL_INC = -I $(RDL_PAT)/include
TOT_FIL	= $(words $(SRC))

all:    $(NAME)

$(NAME): $(OBJ) $(PIP_LIB)
		@$(COMP) -fsanitize=address -g3 $(OBJ) -o $(NAME) $(PIP_LIB) $(RDL_LIB)
		@echo "$(GREEN)Compilation completed.$(NC)"

%.o: %.c
		@$(CC) $(CFLAGS) $(DIR_INC) $(RDL_INC) -c $< -o $@
		@$(eval FILES_DONE := $(shell echo $$(($(FILES_DONE) + 1))))
		@$(call PRINT_LOADING_BAR,$(FILES_DONE),$(TOT_FIL))

$(PIP_LIB):
		@$(MAKE) -C ft_pipex

clean:
		@$(RM) $(OBJ)
		@$(MAKE) -C ft_pipex clean
		@echo "$(GREEN)Cleaning completed.$(NC)"

fclean: clean
		@$(RM) $(NAME)
		@$(MAKE) -C ft_pipex fclean

re:     fclean all
