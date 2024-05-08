/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 07:57:48 by clegros           #+#    #+#             */
/*   Updated: 2024/05/06 07:57:50 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_child_inp(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.tube[0]);
	dup2(pipex.tube[1], 1);
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

static void	second_child_inp(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.tube[1]);
	dup2(pipex.infile, 0);
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

static void	child_mgmt_inp(t_pipex pipex, char *argv[], char *envp[])
{
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		error();
	if (pipex.pid1 == 0)
		first_child_inp(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		error();
	if (pipex.pid2 == 0)
		second_child_inp(pipex, argv, envp);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return ;
}

void	ft_input(char *args[], char *envp[])
{
	t_pipex	redir;

	if (open(args[2], O_RDONLY))
		redir.infile = open(args[2], O_RDONLY);
	redir.outfile = 1;
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
	child_mgmt_inp(redir, args, envp);
	parent_free(&redir);
}
