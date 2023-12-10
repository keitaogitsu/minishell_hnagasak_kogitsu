/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:51:11 by kogitsu           #+#    #+#             */
/*   Updated: 2023/02/09 15:28:05 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p_str;
	size_t	i;

	if (!s || !f)
		return (NULL);
	p_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!p_str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		p_str[i] = f(i, s[i]);
		i++;
	}
	p_str[i] = '\0';
	return (p_str);
}

// #include <stdio.h>
// static int (*f)(int) = NULL;
// static char F(unsigned int i, char c) { (void)i; return (f(c)); };

// int main(void)
// {
// 	f = ft_toupper;
// 	printf("%s\n", ft_strmapi("abcde", F));
// }