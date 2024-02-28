/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:18:42 by kogitsu           #+#    #+#             */
/*   Updated: 2024/02/28 22:35:07 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "lexer.h"

char	*ft_malloc(size_t size)
{
	char	*ptr;

	ptr = (char *)malloc(size);
	if (!ptr)
	{
		// error_exit(NULL);
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void	malloc_error_exit(void)
{
	printf("malloc error\n");
	exit(EXIT_FAILURE);
}

t_token	*token_init(size_t len)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		malloc_error_exit();
	token->str = (char *)malloc(sizeof(char) * (len + 1));
	// token->str = ft_malloc(sizeof(char) * (len + 1));
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

t_token	*tokenize(char *line)
{
	t_tokenizer		tokenizer;
	t_token_type	type;

	if (!line)
		return (NULL);
	tokenizer_init(&tokenizer, line);
	if (*line == '\0')
	{
		ft_debug("line is empty\n");
		complete_current_token(&tokenizer, CHAR_GENERAL);
		free(tokenizer.tmp_token->str);
		free(tokenizer.tmp_token);
		return (tokenizer.tokens_head);
	}
	// print_tokenizer(&tokenizer);
	while (line[tokenizer.line_i] != '\0')
	{
		type = get_type(line[tokenizer.line_i]);
		if (tokenizer.state == STATE_GENERAL)
			general_state_process(&tokenizer, line, type);
		else if (tokenizer.state == STATE_IN_DQUOTE)
			dquote_state_process(&tokenizer, line, type);
		else if (tokenizer.state == STATE_IN_QUOTE)
			quote_state_process(&tokenizer, line, type);
		tokenizer.line_i++;
	}
	if (tokenizer.token_str_i > 0)
		complete_current_token(&tokenizer, type);
	free(tokenizer.tmp_token->str);
	free(tokenizer.tmp_token);
	if (tokenizer.state != STATE_GENERAL)
	{ // QUOTE か DQUOTEが閉じられていない場合
		// error_exit(NULL);
		// print_tokens(tokenizer.tokens_head);
		ft_errmsg("unclosed quote\n");
		return (NULL);
		// exit(EXIT_FAILURE);
	}
	return (tokenizer.tokens_head);
}
