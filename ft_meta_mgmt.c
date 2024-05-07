



#include "minishell.h"

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
        if (*current == '\'' || *current == '"') {
            char quote = *current;
            current++;
            while (*current != '\0' && *current != quote) {
                current++;
            }
            if (*current == '\0') {
                fprintf(stderr, "Erreur: guillemet non fermé\n");
                exit(EXIT_FAILURE);
            }
            current++;
        } else if (*current == '<' || *current == '>' || (*current == '&' && *(current + 1) == '>')) {
            if (current != token_start) {
                *current = '\0';
                add_token(list, token_start);
            }
            char *next_token_start = current;
            if (*current == '&' && *(current + 1) == '>') {
                current += 2;
            } else {
                current++;
            }
            add_token(list, next_token_start);
            token_start = current;
        } else if (*current == ' ') {
            if (current != token_start) {
                *current = '\0';
                add_token(list, token_start);
            }
            current++;
            token_start = current;
        } else {
            current++;
        }
    }

    if (current != token_start) {
        add_token(list, token_start);
    }
}

int main() {
    char cmd[] = "echo 'hello world' > g.txt >> u.txt";

    t_lexer *list = NULL;

    tokenize(cmd, &list);

    // Afficher la liste chaînée
    print_list(list);

    // Libérer la mémoire de la liste chaînée
    free_list(list);

    return 0;
}




static int	ft_meta_str(char *c)
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
}

void	ft_meta_mgmt(char *cmd, char **envp)
{
	char	*arg1;
	char	*arg2;
	char	*meta;
	int		i;

	arg1 = NULL;
	arg2 = NULL;
	i = 0;
	t_lexer	*list;

	list = NULL;
	list = ((t_lexer *)malloc(sizeof(t_lexer)));
	list->str = NULL;

	char	*args[2];

	(void)envp;
	if (list_parkour_str(cmd) >= 1)
	{
		while (cmd[i])
		{
			while (cmd[i] != )
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