
int	list_parkour_str(char *list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (list)
	{
		if (ft_meta(list[j]) > 0)
			i++;
		list = list->next;
	}
	list = head;
	return (i);
}

void	ft_meta_mgmt(char *cmd, char **envp)
{
	char	*arg1;
	char	*arg2;
	char	*meta;
	arg1 = NULL;
	arg2 = NULL;

	char	*args[2];

	(void)envp;
	if (list_parkour(list) >= 1)
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
	}
}