/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:50:03 by kogitsu           #+#    #+#             */
/*   Updated: 2023/02/11 16:28:13 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*p_s;

	i = 0;
	p_s = (const unsigned char *)s;
	while (i < n)
	{
		if (p_s[i] == (unsigned char)c)
			return ((void *)&p_s[i]);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	str[] = "abcdef\0ghij";
// 	char	*p1;
// 	char	*p2;

// 	p1 = memchr(str, 'h', 12);
// 	p2 = ft_memchr(str, 'h', 12);
// 	printf("検索文字は文字列の%ld番目(本家)\n",p1 - str);
// 	printf("検索文字は文字列の%ld番目(ft)\n",p2 - str);
// }