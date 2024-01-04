/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 21:00:13 by kogitsu           #+#    #+#             */
/*   Updated: 2024/01/04 14:11:45 by kogitsu          ###   ########.fr       */
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
	t_token *current;
	
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

void	complete_current_token(t_tokenizer *toker)
{
	toker->tmp_token->str[toker->token_str_i] = '\0';
	join_token(toker,toker->tmp_token);
	toker->tmp_token = token_init(toker->str_len - toker->line_i);
	toker->token_str_i = 0;
	toker->is_quoted = FALSE;
}

void	general_state_process(t_tokenizer *toker, char *line, t_token_type type)
{
	printf("type:%d\n",type);
	if (type == CHAR_QUOTE || type == CHAR_DQUOTE || type == CHAR_ESCAPE
	|| type == CHAR_GENERAL)
	{
		esc_process(toker, line, type);
		if (toker->state == CHAR_QUOTE)
		{
			toker->state = STATE_IN_QUOTE;
			toker->is_quoted = TRUE;
		}
		else if (toker->state == CHAR_DQUOTE)
		{
			toker->state = STATE_IN_DQUOTE;
			toker->is_quoted = TRUE;
		}
		else
			toker->state = STATE_GENERAL;
	}
	else if (type == CHAR_PIPE || type == CHAR_GREATER || type == CHAR_LESSER)
	{
		toker->tmp_token->str[toker->token_str_i++] = line[toker->line_i];
		complete_current_token(toker);
	}
	else if (type == CHAR_WHITESPACE || type == CHAR_TAB)
	{
		printf("## WHITESPACE or TAB%d\n",type);
		// 今作ってるtokenを終わらせる
		if (toker->token_str_i > 0 || (toker->is_quoted))
			complete_current_token(toker);
	}
}