/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:15:09 by kogitsu           #+#    #+#             */
/*   Updated: 2024/03/02 12:15:21 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*ft_malloc(size_t size)
{
	char	*ptr;

	ptr = (char *)malloc(size);
	if (!ptr)
	{
		// error_exit(NULL);
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void	malloc_error_exit(void)
{
	printf("malloc error\n");
	exit(EXIT_FAILURE);
}