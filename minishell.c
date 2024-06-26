/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:39:42 by clegros           #+#    #+#             */
/*   Updated: 2024/04/22 11:05:34 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>



void	minishell_loop(char *line, char **envp)
{
	char	**args;
	t_lexer	*list;
	t_pipex	exec;

	(void)envp;
	list = NULL;
	list = ((t_lexer *)malloc(sizeof(t_lexer)));
	list->str = NULL;
	exec.paths = find_path(envp, &exec);
	exec.cmd_paths = ft_split(exec.paths, ':');
	exec.cmd = NULL;
//	signal(SIGCHLD, SIG_IGN);
	while (1)
	{
		ft_set_input_signals();
		line = readline("minishell>>");
		if (!line)
			break ;
		add_history(line);
		if (!ft_check_quote(line))
		{
			write(2, "Error\n", 6);
			free(line);
		}
		args = &line;
		args = ft_split(*args, '|');

		list = ft_lexero(args, list);
		if (list)
		{
			exec = ft_dispatch(exec, list->str);
			command_executer(args, envp, list, exec);
		}

		/*
		ft_lexer(list);
		ft_parser(list);
		*/



		/*while (list)
		{
			printf("f0ff----%s----|----%d----|----%s----\n", list->str, list->i, list->chr);
			list = list->next;
		}*/
		free(list);
		free(line);
		//free(args);
		args = NULL;
		line = NULL;
//		if (strcmp(list.cmd, "exit") == 0)
//			break ;
//		system("leaks ./minishell");
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;

	(void)argc;
	(void)argv;
	line = malloc(sizeof(char *));
	line = NULL;
	//signal_handler2(SIGINT);
	minishell_loop(line, envp);
}
