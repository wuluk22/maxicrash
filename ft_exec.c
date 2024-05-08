/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:09:06 by clegros           #+#    #+#             */
/*   Updated: 2024/04/09 22:09:09 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_meta(char *c)
{
	if (strcmp(c, "|") == 0)
		return (1);
	if (strcmp(c, "<") == 0)
		return (2);
	if (strcmp(c, ">") == 0)
		return (3);
	if (strcmp(c, "<<") == 0)
		return (4);
	if (strcmp(c, ">>") == 0)
		return (5);
	else
		return (0);
}

void	execute_command(char **envp, char *args, t_pipex exec)
{
	pid_t	pid;
	int		status;
	char	**arg;

	if (list_parkour_str(args) >= 1)
		ft_meta_mgmt(args, envp);
	else
	{
		pid = fork();
		(void)envp;
		arg = ft_split(args, ' ');
		//printf("---%s\n", *arg);
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			while (arg)
			{
				if (execve(exec.cmd, arg, NULL) == -1)
				{
					perror("Error executing command");
					exit(EXIT_FAILURE);
				}
			}
		}
		else
			wait(&status);
	}
}

int	list_parkour(t_lexer *list)
{
	t_lexer	*head;
	int		i;

	head = NULL;
	i = 0;
	while (list)
	{
		head = list;
		if (ft_meta(list->token) > 0)
			i++;
		list = list->next;
	}
	list = head;
	return (i);
}

void	ft_first_iter(char *args[], char *meta, char *envp[])
{
	if (ft_meta(meta) == 1)
		ft_pipex(3, args, envp);
	else if (ft_meta(meta) == 2)
		ft_input(args, envp);
	else if (ft_meta(meta) == 3)
		ft_redir(args, envp);
	else if (ft_meta(meta) == 4)
		ft_heredoc(args, envp);
	else if (ft_meta(meta) == 5)
		ft_append(args, envp);
}

int	ft_stacklen(t_lexer *list)
{
	int		i;

	i = 0;
	while (list != NULL)
	{
		list = list->next;
		i++;
	}
	return (i);
}

void	command_executer(char **args, char **envp, t_lexer *list, t_pipex exec)
{
	int		i;
	//int		j;
	//char	**args;

	i = 0;
	//j = 0;
	//args = NULL;
	if (list->next)
	{
		//printf("!\n");
		while (args[i])
		{
			//printf("1\n");
			//args[j] = ft_strdup(list->str);
			//printf("3\n");
			i++;
			//args++;
			//list = list->next;
			//printf("2\n");
		}
		//i++;
		ft_multi_pipe(i, args, envp);
		//printf("---%d---%s\n", i, args[0]);
		// dup2(1, 0);
		// while (i < 3)
		// {
		// 	ft_multi_pipe(list, envp, i, ft_stacklen(list));
		// 	//list = list->next;
		// 	i++;
		// }
		//list = list->next;
	}
	else
		execute_command(envp, list->str, exec);
	
	//char	*arg1;
	//char	*arg2;
	//char	*meta;
	//arg1 = NULL;
	//arg2 = NULL;
//
	//char	*args[2];
//
	//(void)envp;
	/*if (list_parkour(list) >= 1)
	{
		while (list)
		{
			while (list && ft_meta(list->chr) == 0)
			{
				//printf("jaaaaa\n");
				if (!arg1)
					arg1 = list->str;
				else
				{
					arg1 = ft_strjoin(arg1, " ");
					arg1 = ft_strjoin(arg1, list->str);
				}
				list = list->next;
			}
			//printf("----%s----\n", arg1);
			if (list && ft_meta(list->chr) > 0)
			{
				meta = list->chr;
				list = list->next;
				//printf("--%s\n", list->str);
			}
			while (list && ft_meta(list->chr) == 0)
			{
				if (!arg2)
					arg2 = list->str;
				else
				{
					arg2 = ft_strjoin(arg2, " ");
					arg2 = ft_strjoin(arg2, list->str);
				}
				list = list->next;
			}
			args[0] = arg1;
			args[1] = arg2;
			printf("yooo----%s----%s----\n", args[0], args[1]);
			ft_first_iter(args, meta, envp);

		}
	}*/
}
