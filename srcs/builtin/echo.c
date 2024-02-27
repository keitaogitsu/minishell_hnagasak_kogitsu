/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:08:27 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/25 00:03:54 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "debug.h"

// 変数展開された文字列が渡される前提
void	ft_echo(char *argv[])
{
	int				i;
	unsigned char	opt;

	if (argv[1] == NULL)
	{
		ft_debug("echo: missing argument");
		printf("\n");
		return ;
	}
	opt = 0;
	if (ft_strncmp("-n", argv[1], 2) == 0)
	{
		i = 2;
		opt |= ECHO_OPT_N;
	}
	else
	{
		i = 1;
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
