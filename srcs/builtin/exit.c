/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:23:23 by hnagasak          #+#    #+#             */
/*   Updated: 2023/12/29 20:44:55 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_exit(char *argv[])
{
	int	i;

	if(get_argc(argv) == 1)
		exit(EXIT_SUCCESS);

	// validate argv length is 1 or 2
	// i = 0;
	// while (argv[i])
	// {
	// 	if (ft_isdigit(ft_atoi(argv[i])) == 0)
	// 	{
	// 		ft_putstr_fd("exit\n", STDERR_FILENO);
	// 		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	// 		ft_putstr_fd(argv[i], STDERR_FILENO);
	// 		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	// 		exit(255);
	// 	}
	// 	i++;
	// }
	// exit(ft_atoi(argv[1]));
	// exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
