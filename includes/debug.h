/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:23:31 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/22 21:20:44 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# define DEBUG 0

# include "lexer.h"
# include "libft.h"
# include "utils.h"

void	print_env(t_dlist *env_list);
void	print_tokens(t_token *tokens);
void	print_envlist(t_dlist **env_list);
void	ft_debug(const char *format, ...);

#endif