/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:40:14 by yohanafi          #+#    #+#             */
/*   Updated: 2024/04/22 10:59:33 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*bool	ft_check_quote(char *str)
{
	int		i;
	bool	double_flag;
	bool	single_flag;
	bool	in_double_quotes;
	bool	in_single_quotes;

	i = 0;
	double_flag = true;
	single_flag = true;
	in_double_quotes = false;
	in_single_quotes = false;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOTE && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		if (str[i] == QUOTE && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		i++;
	}
	double_flag = !in_double_quotes;
	single_flag = !in_single_quotes;
	return (double_flag && single_flag);
}*/

#define DOUBLE_QUOTE '\"'
#define SINGLE_QUOTE '\''

bool ft_check_quote(char *str) {
    int i = 0;
    bool in_quotes = false;
	if (str)
	{
    	while (str[i]) {
        	if (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE) {
        	    in_quotes = !in_quotes;
        	}
        	i++;
    	}
	}

    return !in_quotes; // Return true if quotes are balanced, false otherwise
}


static bool	ft_lexer_token(char c)
{
	if (c == QUOTE || c == DOUBLE_QUOTE)
		return (true);
	if (c == PIPE_LINE)
		return (true);
	if (c == REDIR_IN || c == REDIR_OUT)
		return (true);
	return (false);
}

static void	ft_stock_token(char *c, t_lexer *lexer)
{
	lexer->chr = c;
	lexer = lexer->next;
}

static void	ft_scan(t_lexer *lexer)
{
	char	*ptr;

	while (lexer != NULL)
	{
		ptr = lexer->str;
		while (*ptr != '\0')
		{
			if (ft_lexer_token(*ptr))
				ft_stock_token(ptr, lexer);
			ptr++;
		}
		lexer = lexer->next;
	}
}

void	ft_lexer(t_lexer *list)
{
	ft_scan(list);
}
