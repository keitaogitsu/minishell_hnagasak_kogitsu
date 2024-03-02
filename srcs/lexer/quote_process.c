/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:37:40 by kogitsu           #+#    #+#             */
/*   Updated: 2024/03/02 11:59:35 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	quote_state_process(t_tokenizer *toker, char *line, t_token_type type)
{
	(void)type;
	toker->tmp_token->str[toker->token_str_i++] = line[toker->line_i];
	if (line[toker->line_i] == CHAR_QUOTE)
	{
		toker->state = STATE_GENERAL;
	}
}

void	dquote_state_process(t_tokenizer *toker, char *line, t_token_type type)
{
	if (type == CHAR_ESCAPE && line[toker->line_i + 1] != '\0'
		&& ft_strchr("\"\\$", line[toker->line_i + 1]) != NULL)
	{
		toker->tmp_token->str[toker->token_str_i++] = line[toker->line_i++];
		toker->tmp_token->str[toker->token_str_i++] = line[toker->line_i];
	}
	else
	{
		toker->tmp_token->str[toker->token_str_i++] = line[toker->line_i];
		if (line[toker->line_i] == CHAR_DQUOTE)
		{
			toker->state = STATE_GENERAL;
		}
	}
}
