/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:07:35 by clegros           #+#    #+#             */
/*   Updated: 2024/04/22 10:46:45 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipex(int argc, char *args[], char *envp[])
{
	t_pipex	pipex;
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		if (argc == 3)
		{
			pipex.infile = 0;
			pipex.outfile = 1;
			if (pipe(pipex.tube) < 0)
			{
				error();
				return ;
			}
			pipex.paths = find_path(envp, &pipex);
			if (!pipex.paths)
			{
				error();
				return ;
			}
			pipex.cmd_paths = ft_split(pipex.paths, ':');
			child_mgmt(pipex, args, envp);
			parent_free(&pipex);
		}
		else
		{
			ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
			ft_putstr_fd("Ex: <cmd1> <cmd2>\n", 1);
		}
		return ;
	}
}
