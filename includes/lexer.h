/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:14:05 by kogitsu           #+#    #+#             */
/*   Updated: 2023/12/17 15:22:34 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"

typedef	enum	e_type
{
    TOKTYPE_EOF = -1,
TOKTYPE_PARSE_ERROR = 0,
TOKTYPE_NON_EXPANDABLE,
TOKTYPE_EXPANDABLE,
TOKTYPE_EXPANDABLE_QUOTED,
TOKTYPE_PIPE,
TOKTYPE_INPUT_REDIRECTION,
TOKTYPE_HEREDOCUMENT,
TOKTYPE_OUTPUT_REDIRECTION,
TOKTYPE_OUTPUT_APPENDING,
TOKTYPE_SPACE
}	t_type;

typedef	struct	s_token
{
    char            *str;
    t_type	        type;
}	t_token;  



t_list *tokenize(char *line);


#endif