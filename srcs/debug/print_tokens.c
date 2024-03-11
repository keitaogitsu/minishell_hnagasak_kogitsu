/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:27:01 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/11 10:11:11 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static char	*tokentype2str_2(t_token_type type)
{
	if (type == D_GREATER)
		return ("D_GREATER");
	else if (type == D_LESSER)
		return ("D_LESSER");
	else
		return ("UNKNOWN");
}

char	*tokentype2str(t_token_type type)
{
	if (type == CHAR_GENERAL)
		return ("CHAR_GENERAL");
	else if (type == CHAR_PIPE)
		return ("CHAR_PIPE");
	else if (type == CHAR_QUOTE)
		return ("CHAR_QUOTE");
	else if (type == CHAR_DQUOTE)
		return ("CHAR_DQUOTE");
	else if (type == CHAR_WHITESPACE)
		return ("CHAR_WHITESPACE");
	else if (type == CHAR_ESCAPE)
		return ("CHAR_ESCAPE");
	else if (type == CHAR_GREATER)
		return ("CHAR_GREATER");
	else if (type == CHAR_LESSER)
		return ("CHAR_LESSER");
	else if (type == CHAR_TAB)
		return ("CHAR_TAB");
	else if (type == CHAR_NULL)
		return ("CHAR_NULL");
	else
		return (tokentype2str_2(type));
}

/**
 * @brief print tokens->str and tokens->type of each token in tokens
 * @param tokens pointer to the first token of the list
 */
void	print_tokens(t_token *tokens)
{
	char	*str_type;

	while (tokens != NULL)
	{
		str_type = tokentype2str(tokens->type);
		ft_debug("[print_tokens] token:%s type:%s\n", tokens->str, str_type);
		tokens = tokens->next;
	}
}
