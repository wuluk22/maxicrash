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

/*static t_lexer	*ft_parser(t_lexer *list)
{
	t_lexer	*head;

	head = NULL;
	while (list)
	{
		if ((ft_strncmp(list->str, "$", 1) == 0) && (!list->str[1]))
		{
			list = list->next;
			if (ft_strncmp(list->next->str, "=", 1) == 0)
			{
				list->chr = "n";
				list = list->next->next;
				list->chr = "e";
			}
			else
				list->chr = "E";
		}
		list = list->next;
	}
	return (head);
}*/

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
	while ((line = readline("minishell>>")) != NULL)
	{
		add_history(line);
		if (!ft_check_quote(line))
			write(2, "Error\n", 6);
		args = &line;
		args = ft_split(*args, '|');

		list = ft_lexero(args, list);
		exec = ft_dispatch(exec, list->str);
		command_executer(args, envp, list, exec);

		/*
		ft_lexer(list);
		ft_parser(list);
		*/



		/*while (list)
		{
			printf("f0ff----%s----|----%d----|----%s----\n", list->str, list->i, list->chr);
			list = list->next;
		}*/
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
	line = NULL;
	//signal_handler2(SIGINT);
	minishell_loop(line, envp);
}
