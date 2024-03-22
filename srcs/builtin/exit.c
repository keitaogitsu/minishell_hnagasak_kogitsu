/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:23:23 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/22 10:58:37 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exit_status.h"

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
			return (STATUS_NO_NUMERIC_ARG);
		}
		i++;
	}
	return (0);
}

int	ft_exit(char *argv[])
{
	int	exit_status;

	// ft_errmsg("exit\n");
	printf("exit\n");
	exit_status = is_invalid_arg(argv);
	if (exit_status != 0)
		return (exit_status);
	if (argv[1] != NULL)
	{
		exit_status = ft_atoi(argv[1]);
		exit(exit_status);
	}
	exit(EXIT_SUCCESS);
}
