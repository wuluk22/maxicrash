/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utls.bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 12:11:34 by yohanafi          #+#    #+#             */
/*   Updated: 2024/04/30 14:18:35 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	no_path(char **argv, char **envp)
{
	int	i;

	i = 0;
	(void)argv;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	open_file(char *file, int in_out, char **argv, char **envp)
{
	int	rlt;
	//printf("2");
	if (no_path(argv, envp))
		exit(127);
	rlt = 0;
	if (in_out == 0)
		rlt = open(file, O_RDONLY, 0777);
	if (in_out == 1)
		rlt = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (in_out == 2)
		rlt = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (rlt == -1)
	{
		printf("1");
		exit(0);
	}
	//printf("1");
	//printf("5");
	return (rlt);
}

static char	*ft_free_tab(char **tabs)
{
	size_t	i;

	i = 0;
	while (tabs[i])
	{
		free(tabs[i]);
		i++;
	}
	free(tabs);
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_cmd;
	char	*full_paths;
	int		i = 0;

	if (!access(cmd, X_OK))
		return (cmd);
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path_cmd = ft_strjoin(paths[i++], "/");
		full_paths = ft_strjoin(path_cmd, cmd);
		if (!path_cmd)
			free(path_cmd);
		if (!access(full_paths, F_OK))
			return (full_paths);
		if (full_paths)
			free(full_paths);
	}
	return (ft_free_tab(paths));
}

char	*ft_strnstr(const char *find, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!find && !len)
		return (0);
	if (to_find[0] == '\0' || to_find == find)
		return ((char *)find);
	while (find[i] != '\0')
	{
		j = 0;
		while (find[i + j] == to_find[j] && (i + j) < len)
		{
			if (find[i + j] == '\0' && to_find[j] == '\0')
				return ((char *)&find[i]);
			j++;
		}
		if (to_find[j] == '\0')
			return ((char *)(find + i));
		i++;
	}
	return (0);
}