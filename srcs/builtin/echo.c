/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:08:27 by hnagasak          #+#    #+#             */
/*   Updated: 2023/12/17 06:00:29 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

#define ECHO_OPT_N 1

// 変数展開された文字列が渡される前提
void	ft_echo(char *argv[])
{
	int				i;
	unsigned char	opt;

	// printf("--- ft_echo ---\n");
	if (argv[1] == NULL)
	{
		printf("missing argument\n");
		return ;
	}
	opt = 0;
	// オプションの有無を確認
	if (ft_strncmp("-n", argv[1], 2) == 0)
	{
		// printf("has -n option\n");
		i = 2;
		opt |= ECHO_OPT_N;
	}
	else
	{
		// printf("has no -n option\n");
		i = 1;
	}
	while (argv[i] != NULL)
	{
		// printf("argv[%d]:'%s'\n",i,argv[i]);
		printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!(opt & ECHO_OPT_N))
		printf("\n");
}
