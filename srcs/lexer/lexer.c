/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:18:42 by kogitsu           #+#    #+#             */
/*   Updated: 2024/01/04 14:06:35 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*token_init(size_t len)
{
	t_token	*token;
	
	token = (t_token *)malloc(sizeof(t_token));
	if (!token){
		// error_exit(NULL);
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
	token->str = (char *)malloc(sizeof(char) * (len + 1));
	if (!token->str){
		// error_exit(NULL);
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
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
	tokenizer->is_quoted = FALSE;
}

t_token	*tokenize(char *line)
{
	t_tokenizer		tokenizer;
	t_token_type	type;
	if (!line)
		return (NULL);
	tokenizer_init(&tokenizer, line);
	// print_tokenizer(&tokenizer);
	while (line[tokenizer.line_i] != '\0')
	{
		type = get_type(line[tokenizer.line_i]);
		printf("get_type(%c):%d\n",line[tokenizer.line_i],type);
		if (tokenizer.state == STATE_GENERAL)
			general_state_process(&tokenizer, line, type);
		// else if (tokenizer.state == STATE_IN_DQUOTE)
		// 	dquote_state_process(&tokenizer, line, type);
		// else if (tokenizer.state == STATE_IN_QUOTE)
		// 	quote_state_process(&tokenizer, line, type);
		print_tokenizer(&tokenizer);
		tokenizer.line_i++;
	}
	return (tokenizer.tokens_head);
}