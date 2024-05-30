/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:23:31 by hnagasak          #+#    #+#             */
/*   Updated: 2024/05/30 20:46:57 by hnagasak         ###   ########.fr       */
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

# define ECHO_OPT_N 1

// builtin
void	ft_echo(char *argv[]);
int		ft_cd(char *argv[], t_dlist **env_list);
void	ft_pwd(void);
int		ft_exit(char *argv[], int exit_status);
void	ft_env(char **argv, t_dlist **env_list);
int		ft_export(char *argv[], t_dlist **env_list);
int		ft_unset(char *argv[], t_dlist **env_list);

// test
// void	test_is_builtin(char **argv, t_dlist **env_list);
// void	test_builtin(char **argv, t_dlist **env_list);

#endif