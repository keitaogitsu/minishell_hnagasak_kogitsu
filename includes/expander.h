/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:27:37 by kogitsu           #+#    #+#             */
/*   Updated: 2024/02/25 00:03:00 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "exec.h"
# include "lexer.h"
# include "utils.h"

typedef enum e_expandable_state
{
	NOT_IN_QUOTE,
	IN_QUOTE,
	IN_DQUOTE
}		t_expandable_state;

t_token	*expand_env(t_token *tokens, t_dlist **env_list);
char	*replace_env_var(char *str, t_dlist **env_list);

#endif