/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:27:01 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/11 18:25:49 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_env(t_dlist *env_list)
{
	t_env *env;
	t_dlist *current;

	current = env_list;
	printf("--- print_env ----\n");
	while (current)
	{
		// printf("## current:%p, %p\n", current, current->cont);
		env = current->cont;
		printf("%s=%s , is_shell_var = %d\n", env->key, env->value,
			env->is_shell_var);
		// printf("is_shell_var: %d\n", env->is_shell_var);
		current = current->nxt;
	}
	printf("--- end print_env ----\n");
}

char *tokentype2str(t_token_type type)
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
	else if (type == D_GREATER)
		return ("D_GREATER");
	else if (type == D_LESSER)
		return ("D_LESSER");
	else
		return ("UNKNOWN");
}

/**
 * @brief トークンリストを出力する関数。
 *
 * この関数は、与えられたトークンリストを順に走査し、各トークンの内容（文字列とタイプ）を
 * 標準出力に表示します。リストの末尾に達するまで、リストの各ノードに対してこの操作を繰り返します。
 *
 * @param tokens 出力するトークンのリスト。t_token型のポインタです。
 */
void	print_tokens(t_token *tokens)
{
	char *str_type;
	while (tokens != NULL)
	{
		// str_type = tokentype2str(tokens->type);
		// printf("token: %s type:%d\n", tokens->str, tokens->type);
		// printf("[print_tokens]token: %s type:%s\n", tokens->str, str_type);
		printf("[print_tokens]token: %s \n", tokens->str);
		tokens = tokens->next;
	}
}