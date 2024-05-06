/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:09:28 by clegros           #+#    #+#             */
/*   Updated: 2024/04/22 11:01:26 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*ft_lexero(char **args, t_lexer *list)
{
	t_lexer	*head;
	t_lexer	*elem;
	int		i;

	head = NULL;
	i = 0;
	while (args[i] != NULL)
	{
		elem = ft_lstnew(args[i]);
		elem->i = i;
		elem->chr = "w";
		if (!elem)
			return (NULL);
		if (!head)
			head = elem;
		else
			ft_lstadd_back(&list, elem);
		list = elem;
		i++;
	}
	return (head);
}

static char	*duplicate_path(const char *path)
{
    if (path == NULL)
        return NULL;
    return strdup(path);
}

static size_t token_length(const char *token)
{
    size_t len;
	
	len = 0;
    while (token[len] != '\0' && token[len] != ':')
        len++;
    return len;
}

static int check_access(const char *token, const char *command)
{
    size_t command_len;
	size_t token_len;
	
	command_len = strlen(command);

    while (*token != '\0')
	{
		token_len = token_length(token);
        char full_path[token_len + command_len + 2];
        memcpy(full_path, token, token_len);
        full_path[token_len] = '/';
        memcpy(full_path + token_len + 1, command, command_len + 1);
        if (access(full_path, X_OK) == 0)
            return 1;
        token += token_len;
        if (*token == ':')
            token++;
    }
    return (0);
}

static int is_command_valid(const char *command)
{
    char *path;
    char *path_copy;
    char *token; 
    int result;
 
	path = getenv("PATH");
	path_copy = duplicate_path(path);
    
    if (path_copy == NULL)
        return (0);
	token = path_copy;
	result = check_access(token, command);
    free(path_copy);
    return (result);
}

t_pipex	ft_dispatch(t_pipex exec, t_lexer *list)
{
	t_lexer	*head;

	head = NULL;
	while (list)
	{
		//printf("pp----%s----\n", *pipex.cmd_paths);
		if (is_command_valid(list->str))
		{
			list->chr = "c";
			exec.cmd_args = &list->str;
			exec.cmd = parsing(exec.cmd_paths, *exec.cmd_args);
			//printf("pc----%s----\n", exec.cmd);
		}
		list = list->next;
	}
	return (exec);
}
