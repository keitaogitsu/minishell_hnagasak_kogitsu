/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:35:29 by kogitsu           #+#    #+#             */
/*   Updated: 2023/02/10 09:16:14 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1) != NULL)
		s1++;
	i = ft_strlen(s1);
	while (i > 0 && ft_strrchr(set, s1[i]) != NULL)
		i--;
	return (ft_substr(s1, 0, i + 1));
}

// #include <stdio.h>

// int main(void)
// {
// 	char	*s1 = "1234AAA22331122";
// 	char	*set = "1234";

// 	printf("%s\n", ft_strtrim(s1, set));
// }
