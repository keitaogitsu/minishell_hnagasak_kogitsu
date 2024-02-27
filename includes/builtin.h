/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:23:31 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/25 00:02:41 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include "utils.h"
# include <dirent.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <unistd.h>

#define ECHO_OPT_N 1

// builtin
void	ft_echo(char *argv[]);
void	ft_cd(char *argv[], t_dlist **env_list);
void	ft_pwd(void);
void	ft_exit(char *argv[]);
void	ft_env(char **argv, t_dlist **env_list);
void	ft_export(char *argv[], t_dlist **env_list);
void	ft_unset(char *argv[], t_dlist **env_list);

// test
void	test_is_builtin(char **argv, t_dlist **env_list);
void	test_builtin(char **argv, t_dlist **env_list);

#endif