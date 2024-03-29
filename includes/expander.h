/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:27:37 by kogitsu           #+#    #+#             */
/*   Updated: 2024/03/17 18:33:24 by hnagasak         ###   ########.fr       */
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

t_token	*expand_env(t_token *tokens, t_dlist **env_list, int exit_status);
void	replace_env_value(char **str_head, char **start, char *env_value);

// replace_env.c
char	*find_env_value(char *char_position, t_dlist *env_list);
void	copy_str_func(char **new_str, char **src, char end);
void	replace_env_value(char **str_head, char **start, char *env_value);
size_t	toggle_quote_state(size_t state, char *str);
char	*replace_env_var(char *str, t_dlist **env_list, int exit_status);

#endif