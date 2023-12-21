/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:23:23 by hnagasak          #+#    #+#             */
/*   Updated: 2023/12/19 18:33:16 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_exit(char *argv[])
{
	int argc;
	printf("--- ft_exit ---\n");

	argc = 0;
	while(argv[argc])
		argc++;
	printf("argc:%d\n",argc);

	exit(0);
	
	// if (argv[1] == NULL)
	// 	exit(0);
	// else
	// 	exit(atoi(argv[1]));
}