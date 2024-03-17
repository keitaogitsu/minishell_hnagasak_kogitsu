/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:18:42 by kogitsu           #+#    #+#             */
/*   Updated: 2024/03/17 14:08:49 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "lexer.h"
#include "utils.h"

t_token	*token_init(size_t len)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		malloc_error_exit();
	token->str = (char *)malloc(sizeof(char) * (len + 1));
	if (!token->str)
		malloc_error_exit();
	token->str[0] = '\0';
	token->type = CHAR_NULL;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	tokenizer_init(t_tokenizer *tokenizer, char *line)
{
	size_t	line_len;
	t_token	*tokens_head;

	line_len = ft_strlen(line);
	tokens_head = token_init(line_len);
	tokenizer->tmp_token = tokens_head;
	tokenizer->tokens_head = NULL;
	tokenizer->state = STATE_GENERAL;
	tokenizer->line_i = 0;
	tokenizer->token_str_i = 0;
	tokenizer->str_len = line_len;
}

// t_token *finish_tokenize(t_tokenizer *tokenizer)
// {
// 	ft_debug("line is empty\n");
// 	complete_current_token(tokenizer, CHAR_GENERAL);
// 	free(tokenizer->tmp_token->str);
// 	free(tokenizer->tmp_token);
// 	return (tokenizer->tokens_head);
// }

void	proccess_line_by_state(char *line, t_tokenizer *tokenizer,
	t_token_type type)
{
	if (tokenizer->state == STATE_GENERAL)
		general_state_process(tokenizer, line, type);
	else if (tokenizer->state == STATE_IN_DQUOTE)
		dquote_state_process(tokenizer, line, type);
	else if (tokenizer->state == STATE_IN_QUOTE)
		quote_state_process(tokenizer, line, type);
	tokenizer->line_i++;
}

t_token	*tokenize(char *line)
{
	t_tokenizer		tokenizer;
	t_token_type	type;

	if (!line)
		return (NULL);
	tokenizer_init(&tokenizer, line);
	while (line[tokenizer.line_i] != '\0')
	{
		type = get_type(line[tokenizer.line_i]);
		proccess_line_by_state(line, &tokenizer, type);
	}
	if (tokenizer.token_str_i > 0)
		complete_current_token(&tokenizer, type);
	free(tokenizer.tmp_token->str);
	free(tokenizer.tmp_token);
	if (tokenizer.state != STATE_GENERAL)
	{
		ft_errmsg("unclosed quote\n");
		return (NULL);
	}
	ft_debug("--- after tokenize ---\n");
	print_tokens(tokenizer.tokens_head);
	return (tokenizer.tokens_head);
}
