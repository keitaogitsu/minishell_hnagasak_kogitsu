/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:55:18 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/28 00:32:52 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"

// void	test_builtin(char **argv, t_dlist **env_list)
// {
// 	if (ft_strncmp(argv[0], "echo", 4) == 0)
// 		ft_echo(argv);
// 	else if (ft_strncmp(argv[0], "cd", 2) == 0)
// 		ft_cd(argv, env_list);
// 	else if (ft_strncmp(argv[0], "pwd", 3) == 0)
// 		ft_pwd();
// 	else if (ft_strncmp(argv[0], "exit", 4) == 0)
// 		ft_exit(argv);
// 	else if (ft_strncmp(argv[0], "env", 3) == 0)
// 		ft_env(argv, env_list);
// 	else if (ft_strncmp(argv[0], "export", 6) == 0)
// 		ft_export(argv, env_list);
// 	else if (ft_strncmp(argv[0], "unset", 5) == 0)
// 		ft_unset(argv, env_list);
// 	// else if (ft_strncmp(argv[0], "ls", 2) == 0)
// 	// 	ft_execmd(argv, env_list);
// 	else
// 		printf("command not found!!\n");
// 	// else
// 	// test_is_builtin(argv, env_list);
// }