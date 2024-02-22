/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:27:37 by kogitsu           #+#    #+#             */
/*   Updated: 2024/02/03 16:50:35 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

#include "utils.h"
#include "lexer.h"
#include "exec.h"

typedef enum e_expandable_state
{
    NOT_IN_QUOTE,
    IN_QUOTE,
	IN_DQUOTE
} t_expandable_state;

t_token *expand_env(t_token *tokens, t_dlist **env_list);

#endif