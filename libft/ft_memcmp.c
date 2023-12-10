/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 21:43:14 by kogitsu           #+#    #+#             */
/*   Updated: 2023/02/13 12:45:40 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*p;
	const unsigned char	*q;

	i = 0;
	if (n == 0)
		return (0);
	p = (unsigned char *)s1;
	q = (unsigned char *)s2;
	while (i < n)
	{
		if (p[i] != q[i])
			break ;
		i++;
	}
	if (i == n)
		return (0);
	return ((int)(p[i] - q[i]));
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
// 	char buf1[] = "\0abc\0de";      /* 途中に空文字のある文字列 */
// 	char buf2[] = "\0abc\0de";
// 	char buf3[] = "\0abcdef";

// 	printf("----本家の場合------\n");
// 	if (memcmp(buf1, buf2, 7) == 0)
// 		printf("buf1 = buf2\n");
// 	else
// 		printf("buf1 != buf2\n");

// 	if (memcmp(buf1, buf3, 7) == 0)
// 		printf("buf1 = buf3\n");
// 	else
// 		printf("buf1 != buf3\n");
// 	printf("----ftの場合------\n");
// 	if (ft_memcmp(buf1, buf2, 7) == 0)
// 		printf("buf1 = buf2\n");
// 	else
// 		printf("buf1 != buf2\n");

// 	if (ft_memcmp(buf1, buf3, 7) == 0)
// 		printf("buf1 = buf3\n");
// 	else
// 		printf("buf1 != buf3\n");
// 	return 0;
// }