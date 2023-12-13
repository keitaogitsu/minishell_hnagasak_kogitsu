/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:04:44 by kogitsu           #+#    #+#             */
/*   Updated: 2023/02/16 12:45:32 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*p_dst;
	const unsigned char	*p_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	p_dst = (unsigned char *)dst;
	p_src = (const unsigned char *)src;
	while (n--)
		*(p_dst++) = *(p_src++);
	return (dst);
}
