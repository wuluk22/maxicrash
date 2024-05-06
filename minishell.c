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

static char	*spacing(char *args)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = NULL;
	while (args[i])
		i++;
	result = malloc((2 * i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (args[i])
	{
		if ((args[i] == '\'' || args[i] == '\"'))
		{
			result[j++] = ' ';
			result[j++] = args[i];
			result[j++] = ' ';
		}
		else
			result[j++] = args[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

static char	*dollar(char *args)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = NULL;
	while (args[i])
		i++;
	result = malloc((3 * i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (args[i])
	{
		if ((args[i] == '$' && args[i-1] == '\''))
		{
			result[j++] = args[i];
			i++;
			while (args[i] != '\'')
				result[j++] = args[i++];
		}
		if ((args[i] == '$' || args[i] == '=') && args[i-1] != '\'')
		{
			result[j++] = ' ';
			result[j++] = args[i];
			result[j++] = ' ';
		}
		else
			result[j++] = args[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

static t_lexer	*ft_parser(t_lexer *list)
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
}

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
		*args = (dollar(*args));
		*args = (spacing(*args));
		//printf("ff---%s\n", *args);
		args = ft_split(*args, ' ');
		list = ft_lexero(args, list);
		ft_lexer(list);
		ft_parser(list);
		exec = ft_dispatch(exec, list);
		command_executer(envp, list, exec);
		/*while (list)
		{
			printf("f0ff----%s----|----%d----|----%c----\n", list->str, list->i, list->chr);
			list = list->next;
		}*/
		free(line);
		free(args);
		line = NULL;
//		if (strcmp(list.cmd, "exit") == 0)
//			break ;
	//	system("leaks ./minishell");
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
