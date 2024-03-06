/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:27:01 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/05 00:27:34 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_env(t_dlist *env_list)
{
	t_env	*env;
	t_dlist	*current;

	current = env_list;
	ft_debug("--- print_env ----\n");
	while (current)
	{
		env = current->cont;
		ft_debug("%s=%s ,", env->key, env->value);
		ft_debug("is_shell_var = %d\n", env->is_shell_var);
		current = current->nxt;
	}
	printf("--- end print_env ----\n");
}

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

void	print_envlist(t_dlist **env_list)
{
	t_env	*env;
	t_dlist	*current;

	current = *env_list;
	printf("--- print_env ----\n");
	while (current)
	{
		env = (t_env *)current->cont;
		printf("%s=%s , is_shell_var = %d\n", env->key, env->value,
			env->is_shell_var);
		current = current->nxt;
	}
	printf("--- end print_env ----\n");
}

void	ft_debug(const char *format, ...)
{
	va_list	args;

	if (DEBUG)
	{
		va_start(args, format);
		vfprintf(stderr, format, args);
		va_end(args);
	}
}

// void	ft_debug(const char *format, ...)
// {
// 	(void)format;
// }
