/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_mgmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:06:04 by clegros           #+#    #+#             */
/*   Updated: 2024/02/07 13:42:45 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.tube[0]);
	dup2(pipex.tube[1], 1);
	close(pipex.tube[1]);
	//pipex.cmd_args = &argv[0];
	//printf("1---%s---a\n", *pipex.cmd_args);
	pipex.cmd_args = ft_split(argv[0], ' ');
	pipex.cmd = parsing(pipex.cmd_paths, pipex.cmd_args[0]);
	//printf("1----%s\n", *pipex.cmd_paths);
	//printf("1---%s---c\n", pipex.cmd);
	if (!pipex.cmd)
		error();
	//printf("1------------%s----%s-----\n", pipex.cmd, *pipex.cmd_args);
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	second_child(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.tube[1]);
	dup2(pipex.tube[0], 0);
	close(pipex.tube[0]);
//	pipex.cmd_args = &argv[1];
//	printf("2---%s---a\n", pipex.cmd_args[0]);
	pipex.cmd_args = ft_split(argv[1], ' ');
	pipex.cmd = parsing(pipex.cmd_paths, pipex.cmd_args[0]);
	//printf("2----%s\n", *pipex.cmd_paths);
	//printf("2---%s---c\n", pipex.cmd);
	if (!pipex.cmd)
		error();
	//printf("2------------%s----%s-----%s\n", pipex.cmd, pipex.cmd_args[0], pipex.cmd_args[1]);
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	child_mgmt(t_pipex pipex, char *argv[], char *envp[])
{
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		error();
	if (pipex.pid1 == 0)
		first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		error();
	if (pipex.pid2 == 0)
		second_child(pipex, argv, envp);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return ;
}
