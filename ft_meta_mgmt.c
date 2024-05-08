



#include "minishell.h"


int	ft_meta_str(char c)
{
	if (c == '<')
		return (1);
	else if (c == '>')
		return (2);
	else if (c == '|')
		return (3);
	else
		return (0);
}

int	list_parkour_str(char *list)
{
	int	i;
	int	j;
	int meta;

	i = 0;
	j = 0;
	meta = 0;
	while (*list != '\0')
	{
		if (ft_meta_str(*list) > 0)
		{
			if (ft_meta_str(*list) == 1)
				meta = 1;
			else if (ft_meta_str(*list) == 2)
				meta = 2;
			else if (ft_meta_str(*list) == 3)
				meta = 3;
			i++;
		}
		list++;
	}
	return (i);
}

void add_token(t_lexer **list, char *token) {
    t_lexer *new_token = (t_lexer *)malloc(sizeof(t_lexer));
    if (new_token == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    new_token->token = strdup(token);
    new_token->next = NULL;

    if (*list == NULL) {
        *list = new_token;
    } else {
        t_lexer *current = *list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_token;
    }
}

void free_list(t_lexer *list) {
    while (list != NULL) {
        t_lexer *temp = list;
        list = list->next;
        free(temp->token);
        free(temp);
    }
}

void print_list(t_lexer *list) {
    while (list != NULL) {
        printf("%s\n", list->token);
        list = list->next;
    }
}

void tokenize(char *cmd, t_lexer **list) {
    char *token_start = cmd;
    char *current = cmd;

    while (*current != '\0') {
        if (strncmp(current, "<<", 2) == 0 || strncmp(current, ">>", 2) == 0) {

            if (current != token_start) {
                current--;
                *current = '\0';
                current++;	
                add_token(list, token_start);
            }
			if(strncmp(current, "<<", 2) == 0)
				add_token(list, "<<");
			if(strncmp(current, ">>", 2) == 0)
				add_token(list, ">>");

            current += 2; 
            token_start = current;
        }

        else if (*current == '<' || *current == '>') {
            if (current != token_start) {
                current--;
                *current = '\0';
                current++;
                add_token(list, token_start);
            }
			if(strncmp(current, ">", 1) == 0)
				add_token(list, ">");
			if(strncmp(current, "<", 1) == 0)
				add_token(list, "<");

            current++; 
            token_start = current;
        }

        else {
            current++;
        }
    }


    if (current != token_start) {
        add_token(list, token_start);
    }
}

/*static int	ft_meta_str(char *c)
{
	if (strcmp(c, "<") == 0)
		return (1);
	if (strcmp(c, ">") == 0)
		return (2);
	if (strcmp(c, "<<") == 0)
		return (3);
	if (strcmp(c, ">>") == 0)
		return (4);
	else
		return (0);
}

static int	list_parkour_str(char *list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (list)
	{
		if (ft_meta(list[j++]) > 0)
			i++;
		list++;
		printf("list---%s\n", list);
	}
	return (i);
}*/

void	ft_meta_mgmt(char *cmd, char **envp)
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
					args[arg_count++] = list->token;
				list = list->next;
			}
			else if (list && ft_meta(list->token) > 0)
			{
				list->chr = "m";
				args[arg_count++] = list->token;
				list = list->next;
			}
			printf("arg%d = %s\n", i, args[i]);
			i++;
		}
		ft_first_iter(args, envp);
	}
}