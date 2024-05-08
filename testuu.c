#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

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

void add_token(t_lexer **list, char *token) {
    t_lexer *new_token = (t_lexer *)malloc(sizeof(t_lexer));
    if (new_token == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    // strtrim
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



int main() {
    char cmd[] = "echo 'hello world' > g.txt >> u.txt < jojio > ohio < iuhiu > iohio";

    t_lexer *list = NULL;

    tokenize(cmd, &list);


    print_list(list);


    free_list(list);

    return 0;
}
