/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:15:58 by clegros           #+#    #+#             */
/*   Updated: 2023/10/15 21:49:33 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
}

t_lexer	*ft_lstlast(t_lexer *lst)
{
	if (!lst)
		return (NULL);
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

t_lexer	*ft_lstnew(void *content)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->str = content;
	new->next = NULL;
	return (new);
}

