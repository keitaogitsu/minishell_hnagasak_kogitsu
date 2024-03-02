/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:15:09 by kogitsu           #+#    #+#             */
/*   Updated: 2024/03/02 19:13:18 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void	malloc_error_exit(void)
{
	ft_errmsg("malloc error\n");
	exit(EXIT_FAILURE);
}

char	*ft_malloc(size_t size)
{
	char	*ptr;

	ptr = (char *)malloc(size);
	if (!ptr)
		malloc_error_exit();
	return (ptr);
}
