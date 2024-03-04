/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:23:23 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/04 23:55:34 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_invalid_arg(char **argv)
{
	size_t	i;

	if (get_argc(argv) > 2)
	{
		ft_errmsg("minishell: exit: too many arguments\n");
		return (1);
	}
	i = 0;
	while (argv[1] != NULL && argv[1][i] != '\0')
	{
		if (i == 0 && (argv[1][i] == '-' || argv[1][i] == '+'))
			i++;
		if (!ft_isdigit(argv[1][i]))
		{
			ft_errmsg("minishell: exit: numeric argument required\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_exit(char *argv[])
{
	int	status;

	ft_errmsg("exit\n");
	if (is_invalid_arg(argv))
		return ;
	if (argv[1] != NULL)
	{
		status = ft_atoi(argv[1]);
		exit(status);
	}
	exit(EXIT_SUCCESS);
}
