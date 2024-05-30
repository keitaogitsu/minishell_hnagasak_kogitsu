/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:23:23 by hnagasak          #+#    #+#             */
/*   Updated: 2024/05/30 20:36:09 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exit_status.h"

static int	is_numeric_arg(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (i == 0 && (arg[i] == '-' || arg[i] == '+'))
			i++;
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_invalid_arg(char **argv)
{
	if (get_argc(argv) > 1 && !is_numeric_arg(argv[1]))
	{
		ft_errmsg("minishell: exit: numeric argument required\n");
		return (STATUS_NO_NUMERIC_ARG);
	}
	if (get_argc(argv) > 2)
	{
		ft_errmsg("minishell: exit: too many arguments\n");
		return (1);
	}
	return (0);
}

int	ft_exit(char *argv[])
{
	int	exit_status;

	printf("exit\n");
	exit_status = is_invalid_arg(argv);
	if (exit_status == STATUS_NO_NUMERIC_ARG)
		exit(STATUS_NO_NUMERIC_ARG);
	else if (exit_status != 0)
		return (exit_status);
	else if (argv[1] != NULL)
	{
		exit_status = ft_atoi(argv[1]);
		exit(exit_status);
	}
	exit(EXIT_SUCCESS);
}
