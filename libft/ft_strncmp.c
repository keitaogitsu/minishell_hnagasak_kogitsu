/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:21:39 by kogitsu           #+#    #+#             */
/*   Updated: 2023/02/11 16:25:01 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	diff;

	i = 0;
	diff = 0;
	while (i < n)
	{
		diff += ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (diff != 0)
			break ;
		if (s1[i] == '\0' || s2[i] == '\0')
			break ;
		i++;
	}
	return ((int)diff);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char *s1 = "abcdefg";
// 	char *s2 = "accdefg";
// 	char *s3 = "abcdefg";
// 	char *s4 = "abcaefg";
// 	char *s5 = "abcd\0ag";

// 	printf("%d | %d\n", ft_strncmp(s1, s2, 6), strncmp(s1, s2, 6));
// 	printf("%d | %d\n", ft_strncmp(s1, s3, 6), strncmp(s1, s3, 6));
// 	printf("%d | %d\n", ft_strncmp(s1, s4, 6), strncmp(s1, s4, 6));
// 	printf("%d | %d\n", ft_strncmp(s1, s5, 6), strncmp(s1, s5, 6));
// }
