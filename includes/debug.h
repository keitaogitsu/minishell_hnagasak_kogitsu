/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:23:31 by hnagasak          #+#    #+#             */
/*   Updated: 2024/01/07 13:15:25 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "lexer.h"
# include "libft.h"
# include "utils.h"

void	print_env(t_dlist *env_list);
void	print_tokens(t_token *tokens);

#endif