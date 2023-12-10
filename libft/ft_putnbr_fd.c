/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:56:49 by kogitsu           #+#    #+#             */
/*   Updated: 2023/02/09 12:42:31 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_putchar_fd('-', fd);
			ft_putchar_fd((char)(2 + '0'), fd);
			n = 147483648;
		}
		else
		{
			ft_putchar_fd('-', fd);
			n = -n;
		}
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd((char)(n + '0'), fd);
}

// #include <limits.h>

// int	main(void)
// {
// 	ft_putnbr_fd(INT_MIN, 1);
// }
