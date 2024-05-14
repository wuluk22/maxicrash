#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DOUBLE_QUOTE '"'
#define SINGLE_QUOTE '\''

typedef struct s_lexer {
    char *token;
    struct s_lexer *next;
} t_lexer;

void    free_list(t_lexer *list)
{
    while (list != NULL)
    {
        t_lexer *temp = list;
        list = list->next;
        free(temp->token);
        free(temp);
    }
}

void    print_list(t_lexer *list)
{
    while (list != NULL)
    {
        printf("%s\n", list->token);
        list = list->next;
    }
}

void    add_token(t_lexer **list, char *token)
{
    t_lexer *new_token = (t_lexer *)malloc(sizeof(t_lexer));
    if (new_token == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    new_token->token = strdup(token);
    new_token->next = NULL;

    if (*list == NULL)
        *list = new_token;
    else
    {
        t_lexer *current = *list;
        while (current->next != NULL)
            current = current->next;
        current->next = new_token;
    }
}

void    handle_quotes(char current_char, bool *in_quotes, char *current_quote)
{
    if (current_char == DOUBLE_QUOTE || current_char == SINGLE_QUOTE)
    {
        if (*in_quotes && current_char == *current_quote)
        {
            *in_quotes = false;
            *current_quote = '\0';
        }
        else if (!*in_quotes)
        {
            *in_quotes = true;
            *current_quote = current_char;
        }
    }
}

void    add_current_token(t_lexer **list, char **token_start, char *current)
{
    *current = '\0';
    add_token(list, *token_start);
    *token_start = current + 1;
}

void    handle_double_greater(t_lexer **list, char **token_start, char **current)
{
    if (*current != *token_start)
        add_current_token(list, token_start, *current - 1);
    add_token(list, ">>");
    *current += 2;
    *token_start = *current;
}

void    handle_double_less(t_lexer **list, char **token_start, char **current)
{
    if (*current != *token_start)
        add_current_token(list, token_start, *current - 1);
    add_token(list, "<<");
    *current += 2;
    *token_start = *current;
}

void    handle_greater(t_lexer **list, char **token_start, char **current)
{
    if (*current != *token_start)
        add_current_token(list, token_start, *current - 1);
    add_token(list, ">");
    (*current)++;
    *token_start = *current;
}

void    handle_less(t_lexer **list, char **token_start, char **current)
{
    if (*current != *token_start)
        add_current_token(list, token_start, *current - 1);
    add_token(list, "<");
    (*current)++;
    *token_start = *current;
}

void    handle_pipe(t_lexer **list, char **token_start, char **current)
{
    if (*current != *token_start)
        add_current_token(list, token_start, *current - 1);
    add_token(list, "|");
    (*current)++;
    *token_start = *current;
}

void    handle_special_sequences(t_lexer **list, char **token_start, char **current, bool *in_quotes)
{
    if (!*in_quotes)
    {
        if (strncmp(*current, "<<", 2) == 0)
            handle_double_less(list, token_start, current);
        else if (strncmp(*current, ">>", 2) == 0)
            handle_double_greater(list, token_start, current);
        else if (**current == '<')
            handle_less(list, token_start, current);
        else if (**current == '>')
            handle_greater(list, token_start, current);
        else if (**current == '|')
            handle_pipe(list, token_start, current);
    }
}

void tokenize(char *cmd, t_lexer **list)
{
    char *token_start = cmd;
    char *current = cmd;
    bool in_quotes = false;
    char current_quote = '\0';

    while (*current != '\0')
    {
        handle_quotes(*current, &in_quotes, &current_quote);
        handle_special_sequences(list, &token_start, &current, &in_quotes);
        if (!in_quotes && *current == ' ' && current != token_start)
            add_current_token(list, &token_start, current);
        current++;
    }

    if (current != token_start)
        add_token(list, token_start);
}

int main()
{
    char cmd[] = "echo 'hello world' > \"nonnon>\" 'jbnbu>joijo' \"rfrrd\" g.txt >> u.txt < jojio > ohio < iuhiu > iohio | yooooo | jaaa";

    t_lexer *list = NULL;

    tokenize(cmd, &list);

    print_list(list);

    free_list(list);

    return 0;
}
