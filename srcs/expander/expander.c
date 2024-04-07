/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:27:21 by kogitsu           #+#    #+#             */
/*   Updated: 2024/04/07 14:05:29 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "expander.h"
#include "utils.h"

static void	insert_between_tokens(t_token *expanded_tokens, t_token *current,
		t_token **new_tokens_head)
{
	t_token	*expanded_last;

	expanded_last = expanded_tokens;
	if (current->next != NULL)
	{
		while (expanded_last->next != NULL)
			expanded_last = expanded_last->next;
		current->next->prev = expanded_last;
		expanded_last->next = current->next;
	}
	if (current->prev != NULL)
	{
		current->prev->next = expanded_tokens;
		expanded_tokens->prev = current->prev;
	}
	else
		*new_tokens_head = expanded_tokens;
	free(current->str);
	free(current);
	current = NULL;
}

static void	trim_and_change_state(char **str, char **quote_removed_str,
		size_t *state)
{
	if (**str == '\\' && *state == NOT_IN_QUOTE)
	{
		if (*(*str + 1) == '\''
			|| *(*str + 1) == '\"'
			|| ft_isprint(*(*str + 1)))
		{
			(*str)++;
			**quote_removed_str = **str;
			(*quote_removed_str)++;
		}
	}
	else if (**str == '\'' && *state == NOT_IN_QUOTE)
		*state = IN_QUOTE;
	else if (**str == '\'' && *state == IN_QUOTE)
		*state = NOT_IN_QUOTE;
	else if (**str == '\"' && *state == NOT_IN_QUOTE)
		*state = IN_DQUOTE;
	else if (**str == '\"' && *state == IN_DQUOTE)
		*state = NOT_IN_QUOTE;
	else
	{
		**quote_removed_str = **str;
		(*quote_removed_str)++;
	}
}

// 指定したtokenに含まれる引用符を削除する
static t_token	*trim_quotes(t_token *token)
{
	char	*str;
	char	*quote_removed_str;
	char	*rmvd_str_head;
	size_t	state;

	quote_removed_str = ft_malloc(sizeof(char) * (ft_strlen(token->str) + 1));
	rmvd_str_head = quote_removed_str;
	state = NOT_IN_QUOTE;
	str = token->str;
	while (*str != '\0')
	{
		trim_and_change_state(&str, &quote_removed_str, &state);
		str++;
	}
	*quote_removed_str = '\0';
	free(token->str);
	token->str = rmvd_str_head;
	return (token);
}

static void	handle_expanded_tokens(t_token **expanded_tokens, t_token **current,
		t_token **new_tokens_head)
{
	if (*expanded_tokens != NULL)
	{
		insert_between_tokens(*expanded_tokens, *current, new_tokens_head);
		*current = trim_quotes(*expanded_tokens);
	}
	else
	{
		if ((*current)->prev != NULL)
			(*current)->prev->next = (*current)->next;
		if ((*current)->next != NULL)
			(*current)->next->prev = (*current)->prev;
	}
}

t_token	*expand_env(t_token *tokens, t_dlist **env_list, int exit_status)
{
	t_token	*current;
	t_token	*expanded_tokens;
	t_token	*new_tokens_head;

	new_tokens_head = NULL;
	current = tokens;
	while (current != NULL)
	{
		if (current->prev != NULL && current->prev->type == D_LESSER)
		{
			current = current->next;
			continue ;
		}
		current->str = replace_env_var(current->str, env_list, exit_status);
		expanded_tokens = tokenize(current->str);
		handle_expanded_tokens(&expanded_tokens, &current, &new_tokens_head);
		current = current->next;
	}
	ft_debug("--- after expand_env ---\n");
	if (new_tokens_head != NULL)
		print_tokens(new_tokens_head);
	return (new_tokens_head);
}
