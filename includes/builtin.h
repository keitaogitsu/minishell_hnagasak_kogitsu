/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:23:31 by hnagasak          #+#    #+#             */
/*   Updated: 2023/12/19 18:24:22 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include <dirent.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <unistd.h>

// builtin
void	ft_echo(char *argv[]);
void	ft_cd(char *argv[]);
void	ft_pwd(void);
void	ft_exit(char *argv[]);

// libft
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// char	**ft_split(char const *s, char c);
// char	*ft_strjoin(char const *s1, char const *s2);

#endif