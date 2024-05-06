/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils_s.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:17:25 by clegros           #+#    #+#             */
/*   Updated: 2024/04/19 15:17:27 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (!dest || !src)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		size_c;

	size_c = ft_strlen(s1) + 1;
	copy = (char *) malloc(sizeof(char) * (size_c));
	if (copy == NULL)
		return (NULL);
	ft_strcpy(copy, (char *)s1);
	return (copy);
}

char	*ft_strtrim(char const *s1, char set)
{
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	i = 0;
	j = ft_strlen(s1);
	while (s1[i] && ft_strchr(&set, s1[i]))
		i++;
	if (i == ft_strlen(s1))
		return (ft_strdup(""));
	while (j > 0 && ft_strchr(&set, s1[j]))
		j--;
	return (ft_substr(s1, i, j - i + 1));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*s;
	char	*d;

	i = 0;
	s = (char *)src;
	d = (char *)dst;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0') && n > 0)
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
