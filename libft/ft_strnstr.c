/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:49:28 by kogitsu           #+#    #+#             */
/*   Updated: 2023/02/13 18:59:56 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	if (len == 0 && haystack != NULL)
		return (0);
	while (i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*p1;
// 	char	*p2;

// 	printf("本家 | ft\n");
// 	p1 = strnstr("abbbcdefg", "bbc", 20);
// 	p2 = ft_strnstr("abbbcdefg", "bbc", 20);
// 	// printf("%p|%p\n", p1, p2);
// 	// printf("%p | %p\n", strnstr(NULL, "is", 0), ft_strnstr(NULL, "is", 0));
// 	// printf("%p\n", ft_strnstr(NULL, "fake", 3));
// 	// printf("%p\n", strnstr(NULL, "fake", 3));
// 	printf("%p\n", ft_strnstr("fake", NULL, 3));
// 	printf("%p\n", strnstr("fake", NULL, 3));
// }
