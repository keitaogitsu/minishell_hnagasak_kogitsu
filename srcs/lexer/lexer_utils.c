/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:48:51 by kogitsu           #+#    #+#             */
/*   Updated: 2024/01/04 13:48:08 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token_type	get_type(char c)
{
	const char	*char_list;
	
	char_list = "|\'\" \t\\><";
	while (*char_list != '\0')
	{
		if (*char_list == c)
			return ((t_token_type)c);
		char_list++;
	}
	return (CHAR_GENERAL);
}

void print_tokenizer(t_tokenizer *tokenizer)
{
	printf("--- print_toknizer ---\n");
	printf("line_i:%zu\n",tokenizer->line_i);
	printf("token_str_i:%zu\n",tokenizer->token_str_i);
	printf("str_len:%zu\n",tokenizer->str_len);
	printf("is_quoted:%d\n",tokenizer->is_quoted);
	printf("tmp_token:%s\n",tokenizer->tmp_token->str);
	if(tokenizer->tokens_head != NULL)
		printf("tokens_head:%s\n",tokenizer->tokens_head->str);
	else
		printf("tokens_head: NULL\n");
	printf("state:%d\n",tokenizer->state);
}