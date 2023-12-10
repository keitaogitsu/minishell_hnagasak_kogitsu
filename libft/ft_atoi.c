/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:17:02 by kogitsu           #+#    #+#             */
/*   Updated: 2023/02/13 19:54:17 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\r' || c == '\v' || \
		c == '\f' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

static size_t	ft_flow_check(size_t num, int minus_flag, size_t n)
{
	size_t	ov_div;
	size_t	ov_mod;

	ov_div = LONG_MAX / 10;
	ov_mod = LONG_MAX % 10;
	if ((!minus_flag) && ((num > ov_div) || (num == ov_div && n > ov_mod)))
		return (LONG_MAX);
	else if (minus_flag && \
			((num > ov_div) || (num == ov_div && n > ov_mod + 1)))
		return (LONG_MIN);
	else
		return (num);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		minus_flag;
	long	n;

	i = 0;
	minus_flag = 0;
	n = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			minus_flag = 1;
	while (ft_isdigit(str[i]))
	{
		n = ft_flow_check(n, minus_flag, (size_t)(str[i] - '0'));
		if (n == LONG_MAX)
			return ((int)LONG_MAX);
		else if (n == LONG_MIN)
			return ((int)LONG_MIN);
		n = n * 10 + (str[i++] - '0');
	}
	if (minus_flag)
		n *= -1;
	return ((int)n);
}

// #include <stdlib.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	str1[] = "9223372036854775806";
// 	char	str2[] = "-9223372036854775807";
// 	int		num1, num2;

// 	printf("-----本家-----\n");
// 	num1 = atoi(str1);
// 	printf("[9223372036854775806]の値は:%d\n", num1);
// 	num2 = atoi(str2);
// 	printf("[-9223372036854775807]の値は:%d\n", num2);

// 	printf("-----ft-----\n");
// 	num1 = ft_atoi(str1);
// 	printf("[9223372036854775806]の値は:%d\n", num1);
// 	num2 = ft_atoi(str2);
// 	printf("[-9223372036854775807]の値は:%d\n", num2);
// }
