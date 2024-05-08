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

static int	list_parkour_init(t_lexer *list)
{
	t_lexer	*head;
	int		i;

	head = NULL;
	i = 0;
	while (list)
	{
		head = list;
		if (ft_meta(list->str) > 0)
			i++;
		list = list->next;
	}
	list = head;
	return (i);
}

void	ft_first_iter(char *args[], char *envp[])
{
	if (ft_meta(args[1]) == 1)
		ft_pipex(3, args, envp);
	else if (ft_meta(args[1]) == 2)
		ft_input(args, envp);
	else if (ft_meta(args[1]) == 3)
		ft_redir(args, envp);
	else if (ft_meta(args[1]) == 4)
		ft_heredoc(args, envp);
	else if (ft_meta(args[1]) == 5)
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
	int	i;

	i = 0;

	if(list_parkour_init(list) > 0)
	{
		while (args[i])
			i++;
		ft_multi_pipe(i, args, envp);
	}
	else
		execute_command(envp, list->str, exec);
}



/*static int	list_parkour_str_v(char **list)
{
	int	i;
	int	j;
	int meta;

	i = 0;
	j = 0;
	meta = 0;
	while (**list != '\0')
	{
		if (ft_meta_str(**list) > 0)
		{
			if (ft_meta_str(**list) == 1)
				meta = 1;
			else if (ft_meta_str(**list) == 2)
				meta = 2;
			else if (ft_meta_str(**list) == 3)
				meta = 3;
			i++;
		}
		list++;
	}
	return (meta);
}

static int	list_parkour_strstr(char **list)
{
	int	i;
	int	j;
	int meta;

	i = 0;
	j = 0;
	meta = 0;
	while (**list != '\0')
	{
		printf("-1-\n");
		if (ft_meta_str(**list) > 0)
		{
			printf("-2-\n");
			if (ft_meta_str(**list) == 1)
				meta = 1;
			else if (ft_meta_str(**list) == 2)
				meta = 2;
			else if (ft_meta_str(**list) == 3)
					meta = 3;
			printf("-4-\n");
			i++;
		}
		printf("-5-\n");
		list++;
	}
	return (i);
}
void	ft_meta_mgmt_first(char *cmd, char **envp)
{
	printf("---cmd---%s\n", cmd);
	int		i;

	i = 0;
	t_lexer	*list;

	list = NULL;

	char	*args[100]; // max files ??? 
	int		arg_count;
	arg_count = 0;

	(void)envp;
	//printf("2-2\n");
	tokenize(cmd, &list);
	//printf("1-1\n");
	print_list(list);
	if (list_parkour(list) >= 1)
	{
		while (list)
		{
			if (list && ft_meta(list->token) == 0)
			{
				//printf("jaaaaa\n");
				if (arg_count <= 100)
					args[arg_count++] = list->str;
				list = list->next;
			}
			else if (list && ft_meta(list->token) > 0)
			{
				list->chr = "m";
				args[arg_count++] = list->str;
				list = list->next;
			}
			printf("arg%d = %s\n", i, args[i]);
			i++;
		}
		ft_first_iter(args, envp);
	}
}*/
