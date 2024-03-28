/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:08:27 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/27 21:24:24 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "debug.h"

void	ft_echo(char *argv[])
{
	int				i;
	unsigned char	opt;

	if (argv[1] == NULL)
	{
		printf("\n");
		return ;
	}
	opt = 0;
	i = 1;
	while (ft_strncmp("-n", argv[i], 3) == 0)
	{
		i++;
		opt |= ECHO_OPT_N;
	}
	while (argv[i] != NULL)
	{
		printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!(opt & ECHO_OPT_N))
		printf("\n");
}
