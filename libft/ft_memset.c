/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:08:15 by kogitsu           #+#    #+#             */
/*   Updated: 2023/01/28 14:30:39 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int val, size_t len)
{
	size_t			count;
	unsigned char	*a;

	count = 0;
	a = (unsigned char *)dst;
	while (count < len)
	{
		a[count] = (unsigned char)val;
		count++;
	}
	return (dst);
}
