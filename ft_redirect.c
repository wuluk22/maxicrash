/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:45:40 by clegros           #+#    #+#             */
/*   Updated: 2024/04/17 17:45:43 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_child_red(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.tube[0]);
	dup2(1, 1);
	close(pipex.tube[1]);
	pipex.cmd_args = ft_split(argv[0], ' ');
	pipex.cmd = parsing(pipex.cmd_paths, pipex.cmd_args[0]);

	if (!pipex.cmd)
		error();
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

static void	second_child_red(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.tube[1]);
	dup2(pipex.outfile, 1);
	close(pipex.tube[0]);
	pipex.cmd_args = ft_split(argv[0], ' ');
	pipex.cmd = parsing(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
		error();
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

static void	child_mgmt_red(t_pipex pipex, char *argv[], char *envp[])
{
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		error();
	if (pipex.pid1 == 0)
		first_child_red(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		error();
	if (pipex.pid2 == 0)
		second_child_red(pipex, argv, envp);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return ;
}

void	ft_redir(char *args[], char *envp[])
{
	t_pipex	redir;

	redir.infile = 0;
	redir.outfile = open(args[1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (pipe(redir.tube) < 0)
	{
		error();
		return ;
	}
	redir.paths = find_path(envp, &redir);
	if (!redir.paths)
	{
		error();
		return ;
	}
	redir.cmd_paths = ft_split(redir.paths, ':');
	child_mgmt_red(redir, args, envp);
	parent_free(&redir);
}
