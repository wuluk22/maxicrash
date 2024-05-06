/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:38:45 by clegros           #+#    #+#             */
/*   Updated: 2024/04/22 10:48:29 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>
# include "ft_pipex/pipex.h"

enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
};

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};

typedef struct s_lexer
{
	char				*str;
	char				*chr;
	int					i;
//	enum				e_token;
//	enum				e_state;
	struct s_lexer		*prev;
	struct s_lexer		*next;
}	t_lexer;

//void		rl_replace_line(const char *text, int clear_undo);
//-------------------------------EXECUTION--------------------------------//
void		command_executer(char **envp, t_lexer *list, t_pipex exec);
void		ft_multi_pipe(t_lexer *list, char **envp, int i, int len);
void		ft_first_iter(char *args[], char *meta, char *envp[]);
int			ft_meta(char *c);
int			list_parkour(t_lexer *list);
void		execute_command(char **envp, t_lexer *list, t_pipex exec);
void		ft_redir(char *args[], char *envp[]);
void		ft_input(char *args[], char *envp[]);
void		ft_append(char *args[], char *envp[]);
void		ft_heredoc(char *args[], char *envp[]);

//--------------------------------LOOPING---------------------------------//
void		minishell_loop(char *line, char **envp);

//--------------------------------SIGNALS---------------------------------//
void		ft_signal_handler(int sign);
void		ft_set_input_signals(void);
//void		ft_signal_handler2(int sign);

//---------------------------------LEXER----------------------------------//
t_lexer		*ft_lexero(char **args, t_lexer *list);
t_pipex		ft_dispatch(t_pipex exec, t_lexer *list);
void		ft_lexer(t_lexer *list);
bool		ft_check_quote(char *str);

//----------------------------------FREE----------------------------------//
void		ft_free(char *line, t_lexer elem);

void		ft_lstadd_back(t_lexer **lst, t_lexer *new);
t_lexer		*ft_lstlast(t_lexer *lst);
t_lexer		*ft_lstnew(void *content);

//--------------------------------STR_UTILS--------------------------------//

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_strtrim(char const *s1, char set);
char		*ft_strchr(char *s, int c);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_strncmp(char *s1, char *s2, size_t n);

#endif
