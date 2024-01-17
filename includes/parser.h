/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:21:28 by kogitsu           #+#    #+#             */
/*   Updated: 2024/01/17 21:41:08 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "utils.h"
#include "lexer.h"
#include "exec.h"

t_dlist	**create_cmd_list(t_token *tokens, t_dlist **env_list);

#endif