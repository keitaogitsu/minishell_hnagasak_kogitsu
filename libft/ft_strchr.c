/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:09:44 by kogitsu           #+#    #+#             */
/*   Updated: 2023/02/13 12:53:24 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	*str = "abcdefga";
// 	int		c1 = 'd';
// 	int		c2 = 'h';
// 	int		c3 = '\0';
// 	int		c4 = 'a';

// 	printf("dの場合:(ft)%p/(本家)%p\n", ft_strchr(str, c1), strchr(str, c1));
// 	printf("hの場合:(ft)%p/(本家)%p\n", ft_strchr(str, c2), strchr(str, c2));
// 	printf("nul文字の場合:(ft)%p/(本家)%p\n", ft_strchr(str, c3), strchr(str, c3));
// 	printf("aの場合:(ft)%p/(本家)%p\n", ft_strchr(str, c4), strchr(str, c4));
// 	printf("%d:'a' - 256", (c4 - 256)%256);
// }
