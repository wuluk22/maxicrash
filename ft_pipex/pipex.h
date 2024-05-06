/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:07:42 by clegros           #+#    #+#             */
/*   Updated: 2024/02/07 11:07:45 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}	t_pipex;

char	*find_path(char **envp, t_pipex *pipex);
void	child_mgmt(t_pipex pipex, char *argv[], char *envp[]);
char	*parsing(char **cmd_paths, char *cmd_args);
void	first_child(t_pipex pipex, char *argv[], char *envp[]);
void	second_child(t_pipex pipex, char *argv[], char *envp[]);
void	parent_free(t_pipex *pipex);
void	child_free(t_pipex *pipex);
void	error(void);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
char	**ft_split(char *str, char c);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_pipex(int argc, char *args[], char *envp[]);

#endif