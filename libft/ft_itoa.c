/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:17:48 by kogitsu           #+#    #+#             */
/*   Updated: 2023/02/16 16:45:34 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	digit_count(int num)
{
	size_t	digit_size;

	digit_size = 1;
	if (num < 0)
	{
		num *= -1;
		digit_size++;
	}
	while (num > 9)
	{
		num /= 10;
		digit_size++;
	}
	return (digit_size);
}

static char	*return_intmin(void)
{
	char	*res;

	res = (char *)ft_calloc(12, sizeof(char));
	if (!res)
		return (NULL);
	ft_memcpy(res, "-2147483648", 11);
	return (res);
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	size;

	if (n == INT_MIN)
		return (return_intmin());
	size = digit_count(n);
	result = (char *)ft_calloc(size + 1, sizeof(char));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		result[0] = '-';
	}
	while (n > 9)
	{
		result[size - 1] = '0' + (n % 10);
		size--;
		n /= 10;
	}
	result[size - 1] = '0' + n;
	return (result);
}

// int main(void)
// {
// 	int a = INT_MAX - 1;
// 	char	*s;

// 	s = ft_itoa(a);
// 	for (int i = 0; i < 11; i++)
// 		printf("%c,", s[i]);
// }