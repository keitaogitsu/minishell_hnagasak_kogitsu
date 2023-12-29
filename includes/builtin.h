/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:23:31 by hnagasak          #+#    #+#             */
/*   Updated: 2023/12/29 18:50:03 by hnagasak         ###   ########.fr       */
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

// typedef struct s_var
// {
// 	const char		*key;
// 	const char		*value;
// 	int			is_shell_var;
// 	struct s_var	*next;
// }					t_var;

// builtin
void	ft_echo(char *argv[]);
void	ft_cd(char *argv[]);
void	ft_pwd(void);
void	ft_exit(char *argv[]);
void	ft_env(t_dlist **env_list);
void	ft_export(char *argv[], t_dlist **env_list);
void	ft_unset(char *argv[], t_dlist **env_list);

// libft
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// char	**ft_split(char const *s, char c);
// char	*ft_strjoin(char const *s1, char const *s2);

#endif