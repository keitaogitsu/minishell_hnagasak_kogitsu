/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:11:28 by kogitsu           #+#    #+#             */
/*   Updated: 2024/02/08 22:14:20 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// rec("a    bb   ccc dddd",' ', 0) -> "a","bb","ccc","ddd",NULL
// rec("   bb   ccc dddd",' ', 1) -> NULL,"bb","ccc","ddd",NULL
// rec("   ccc dddd",' ', 2) -> NULL,NULL,"ccc","ddd",NULL
// rec(" dddd",' ', 3) -> NULL,NULL,NULL,"dddd",NULL
// rec("",' ', 4) -> NULL,NULL,NULL,NULL,NULL

static char	**end_processing(char **container, int i)
{
	container = (char **)malloc((i + 1) * sizeof(char *));
	if (!container)
		return (NULL);
	container[i] = NULL;
	return (container);
}

static char	**rec(char const *s, char c, int i)
{
	char const	*ptr;
	char		**container;

	container = NULL;
	while (*s == c && c != '\0')
		s++;
	if (*s == '\0')
		return (end_processing(container, i));
	ptr = s;
	while (*s && *s != c)
		s++;
	ptr = ft_substr(ptr, 0, s - ptr);
	if (!ptr)
		return (NULL);
	container = rec(s, c, i + 1);
	if (!container)
	{
		free((void *)ptr);
		return (NULL);
	}
	container[i] = (char *)ptr;
	return (container);
}

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (rec(s, c, 0));
}

// #include <stdio.h>

// int main(void)
// {
// 	char * * tab;

// 	tab = ft_split("trip ouil le", ' ');
// 	for (int i=0; i<3; i++)
// 		printf("%s\n", tab[i]);
// }
