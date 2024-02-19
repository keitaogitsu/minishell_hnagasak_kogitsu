/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:48:51 by kogitsu           #+#    #+#             */
/*   Updated: 2024/02/20 06:09:33 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "debug.h"

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
	ft_debug("--- print_tokenizer ---\n");
	ft_debug("line_i:%zu\n",tokenizer->line_i);
	ft_debug("token_str_i:%zu\n",tokenizer->token_str_i);
	ft_debug("str_len:%zu\n",tokenizer->str_len);
	ft_debug("tmp_token:%s\n",tokenizer->tmp_token->str);
	if(tokenizer->tokens_head != NULL)
		ft_debug("tokens_head:%s\n",tokenizer->tokens_head->str);
	else
		ft_debug("tokens_head: NULL\n");
	ft_debug("state:%d\n",tokenizer->state);
}