/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 21:00:13 by kogitsu           #+#    #+#             */
/*   Updated: 2024/01/20 14:17:29 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	esc_process(t_tokenizer *toker, char *line, t_token_type type)
{
	if (type == CHAR_ESCAPE && line[toker->line_i + 1] != '\0')
	{
		toker->tmp_token->str[toker->token_str_i++] = line[toker->line_i++];
		toker->tmp_token->str[toker->token_str_i++] = line[toker->line_i];
	}
	else
		toker->tmp_token->str[toker->token_str_i++] = line[toker->line_i];
}

void	join_token(t_tokenizer *toker, t_token *new)
{
	t_token	*current;

	if (toker->tokens_head == NULL)
	{
		toker->tokens_head = new;
		toker->tmp_token = new;
	}
	else
	{
		current = toker->tokens_head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

void	complete_current_token(t_tokenizer *toker, t_token_type type)
{
	toker->tmp_token->type = type;
	toker->tmp_token->str[toker->token_str_i] = '\0';
	join_token(toker, toker->tmp_token);
	toker->tmp_token = token_init(toker->str_len - toker->line_i);
	toker->token_str_i = 0;
	printf("tokenizer.state = %d\n", toker->state);
}

void	general_state_process(t_tokenizer *toker, char *line, t_token_type type)
{
	// printf("general_state_process type:%d\n", type);
	if (type == CHAR_QUOTE || type == CHAR_DQUOTE || type == CHAR_ESCAPE
		|| type == CHAR_GENERAL)
	{
		esc_process(toker, line, type);
		if (type == CHAR_QUOTE)
			toker->state = STATE_IN_QUOTE;
		else if (type == CHAR_DQUOTE)
			toker->state = STATE_IN_DQUOTE;
		else
			toker->state = STATE_GENERAL;
	}
	else if (type == CHAR_PIPE || type == CHAR_GREATER || type == CHAR_LESSER)
	{
		if (toker->token_str_i > 0)
			complete_current_token(toker, CHAR_GENERAL);
		toker->tmp_token->str[toker->token_str_i++] = line[toker->line_i];
		if ((type == CHAR_GREATER || type == CHAR_LESSER) && 
			line[toker->line_i + 1] == line[toker->line_i])
		{
			toker->tmp_token->str[toker->token_str_i++] = line[toker->line_i++];
			if (type == CHAR_GREATER)
				type = D_GREATER;
			else if (type == CHAR_LESSER)
				type = D_LESSER;
		}
		complete_current_token(toker, type);
	}
	else if (type == CHAR_WHITESPACE || type == CHAR_TAB)
	{
		// 今作ってるtokenを終わらせる
		if (toker->token_str_i > 0)
			complete_current_token(toker, CHAR_GENERAL);
	}
}
