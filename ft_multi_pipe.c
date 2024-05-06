#include "minishell.h"

static void	executor(t_lexer *list, char **envp)
{
	char	*arg1;
	char	*arg2;
	char	*meta;
	arg1 = NULL;
	arg2 = NULL;
	t_pipex	exec;
	exec.paths = find_path(envp, &exec);
	exec.cmd_paths = ft_split(exec.paths, ':');
	exec.cmd = NULL;

	char	*args[2];
	exec = ft_dispatch(exec, list);
	if (list_parkour(list) >= 1)
	{
		while (list)
		{
			arg1 = NULL;
			arg2 = NULL;
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
			// if (list && ft_meta(list->chr) > 0)
			// {
			// 	meta = list->chr;
			// 	list = list->next;
			// 	//printf("--%s\n", list->str);
			// }
			// while (list && ft_meta(list->chr) == 0)
			// {
			// 	if (!arg2)
			// 		arg2 = list->str;
			// 	else
			// 	{
			// 		arg2 = ft_strjoin(arg2, " ");
			// 		arg2 = ft_strjoin(arg2, list->str);
			// 	}
			// 	list = list->next;
			// }
			args[0] = arg1;
			args[1] = arg2;
			printf("yooo----%s----%s----\n", args[0], args[1]);
			if (list) {
				ft_first_iter(args, &list, list->chr, envp);
				if (list)
					list->next;
			} else { // absolute last "command"
				execute_command(), but while reading pipe input;
			}
		}
	}
	else
		execute_command(envp, list, exec);
}

void	ft_multi_pipe(t_lexer *list, char **envp, int i, int len)
{
	(void)i;
	(void)len;
	executor(list, envp);
	return ;
	pid_t	pid;
	t_pipex	exec;

	//exec = ft_dispatch(exec, list);
	if (pipe(exec.tube) == -1)
	{
		printf("1\n");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		printf("1\n");
		exit(1);
	}
	if (!pid)
	{
		printf("2\n");
		close(exec.tube[0]);
		if (i <= len - 2)
			dup2(exec.tube[1], 1);
		close(exec.tube[1]);
		executor(list, envp);
	}
}
