/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 21:17:12 by kogitsu           #+#    #+#             */
/*   Updated: 2023/02/11 16:02:37 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	len;

// 	len = 0;
// 	while (s[len] != '\0')
// 		len++;
// 	return (len);
// }

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d_size;
	size_t	s_size;

	i = 0;
	if ((dst == NULL && size == 0) || (size == 0))
		return (ft_strlen(src));
	d_size = ft_strlen(dst);
	s_size = ft_strlen(src);
	if (d_size >= size)
		return (size + s_size);
	while (i + d_size + 1 < size && src[i])
	{
		dst[d_size + i] = src[i];
		i++;
	}
	dst[d_size + i] = '\0';
	return (d_size + s_size);
}

// #include <string.h>
// #include <stdio.h>

// int main(void)
// {
// 	char *src = "ABC";
// 	char *src1 = calloc(100, sizeof(char));
// 	char *src2 = calloc(100, sizeof(char));
// 	for (int i = 0; i < 99; i++)
// 	{
// 		src1[i] = i + 1;
// 		src2[i] = i + 1;
// 	}
// 	printf("%zu\n", ft_strlcat("helloworld", src1, 0));
// 	printf("%lu\n", strlcat("helloworld", src2, 0));
// }