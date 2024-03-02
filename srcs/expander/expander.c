/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:27:21 by kogitsu           #+#    #+#             */
/*   Updated: 2024/03/02 14:33:18 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "expander.h"

/**
 * @brief Retrieves the value of an environment variable from a list.
 * @param char_position Pointer to the start of the variable name.
 * @param env_list Pointer to the list of environment variables.
 * @return The variable's value if found, else an empty string.
 */
char	*find_env_value(char *char_position, t_dlist *env_list)
{
	char	*start;
	t_env	*env;

	if (*char_position == '$')
	{
		char_position++;
		start = char_position;
		while (*char_position != '\"' && *char_position != '\''
			&& *char_position != ' ' && *char_position != '$'
			&& *char_position != '\0')
			char_position++;
		while (env_list != NULL)
		{
			env = (t_env *)env_list->cont;
			if (ft_strncmp(env->key, start, ft_strlen(env->key)) == 0
				&& (*char_position == '\"' || *char_position == '\''
					|| *char_position == ' ' || *char_position == '$'
					|| *char_position == '\0'))
				return (((t_env *)(env_list)->cont)->value);
			env_list = (env_list)->nxt;
		}
		return ("");
	}
	return (NULL);
}

void	copy_str_func(char **new_str, char **src, char end)
{
	while (**src != end)
	{
		**new_str = **src;
		(*new_str)++;
		(*src)++;
	}
}

/**
 * @brief Expands the first environment variable in a string with env_value.
 * @param str The input string to be replaced.
 * @param env_value The value to replace the environment variable with.
 * @return A new string with the first environment variable replaced.
 */
char	*replace_1st_env_var(char *str, char *env_value)
{
	size_t	value_len;
	size_t	str_len;
	char	*new_str;
	char	*new_str_head;

	value_len = ft_strlen(env_value);
	str_len = ft_strlen(str);
	new_str = (char *)malloc(sizeof(char) * (str_len + value_len + 1));
	if (new_str == NULL)
		return (NULL);
	new_str_head = new_str;
	copy_str_func(&new_str, &str, '$');
	str++;
	while (*str != '\"' && *str != '\'' && *str != ' ' && *str != '$'
		&& *str != '\0')
		str++;
	copy_str_func(&new_str, &env_value, '\0');
	copy_str_func(&new_str, &str, '\0');
	*new_str = '\0';
	return (new_str_head);
}

void	insert_between_tokens(t_token *expanded_tokens, t_token *current,
		t_token **new_tokens_head)
{
	t_token	*expanded_last;

	expanded_last = expanded_tokens;
	if (current->next != NULL)
	{
		current->next->prev = expanded_tokens;
		while (expanded_last->next != NULL)
			expanded_last = expanded_last->next;
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

void	trim_and_change_state(char **str, char **quote_removed_str, size_t *state)
{
	if (**str == '\\' && *(*str + 1) == '\'' && *state == NOT_IN_QUOTE)
		**quote_removed_str++ = *++(*str);
	else if (**str == '\\' && *(*str + 1) == '\"' && *state == NOT_IN_QUOTE)
		**quote_removed_str++ = *++(*str);
	else if (**str == '\'' && *state == NOT_IN_QUOTE)
		*state = IN_QUOTE;
	else if (**str == '\'' && *state == IN_QUOTE)
		*state = NOT_IN_QUOTE;
	else if (**str == '\"' && *state == NOT_IN_QUOTE)
		*state = IN_DQUOTE;
	else if (**str == '\"' && *state == IN_DQUOTE)
		*state = NOT_IN_QUOTE;
	else
		**quote_removed_str++ = **str;
}

// 指定したtokenに含まれる引用符を削除する
static t_token	*trim_quotes(t_token *token)
{
	char	*str;
	char	*quote_removed_str;
	char	*rmvd_str_head;
	size_t	state;

	quote_removed_str = (char *)malloc(sizeof(char) * (ft_strlen(token->str)
				+ 1));
	rmvd_str_head = quote_removed_str;
	state = NOT_IN_QUOTE;
	str = token->str;
	while (*str != '\0')
	{
		// trim_and_change_state(&str, &quote_removed_str, &state);
		if (*str == '\\' && *(str + 1) == '\'' && state == NOT_IN_QUOTE)
		{
			str++;
			*quote_removed_str = *str;
			quote_removed_str++;
		}
		else if (*str == '\\' && *(str + 1) == '\"' && state == NOT_IN_QUOTE)
		{
			str++;
			*quote_removed_str = *str;
			quote_removed_str++;
		}
		else if (*str == '\'' && state == NOT_IN_QUOTE)
			state = IN_QUOTE;
		else if (*str == '\'' && state == IN_QUOTE)
			state = NOT_IN_QUOTE;
		else if (*str == '\"' && state == NOT_IN_QUOTE)
			state = IN_DQUOTE;
		else if (*str == '\"' && state == IN_DQUOTE)
			state = NOT_IN_QUOTE;
		else
		{
			*quote_removed_str = *str;
			quote_removed_str++;
		}
		str++;
	}
	*quote_removed_str = '\0';
	free(token->str);
	token->str = rmvd_str_head;
	return (token);
}

char	*replace_env_var(char *str, t_dlist **env_list)
{
	char	*env_value;
	char	*replaced_str;
	size_t	state;
	char	*str_head;
	int		is_replaced_str;

	is_replaced_str = 0;
	state = NOT_IN_QUOTE;
	str_head = str;
	while (*str != '\0')
	{
		if (*str == '\'' && state == NOT_IN_QUOTE)
			state = IN_QUOTE;
		else if (*str == '\'' && state == IN_QUOTE)
			state = NOT_IN_QUOTE;
		else if (*str == '\"' && state == NOT_IN_QUOTE)
			state = IN_DQUOTE;
		else if (*str == '\"' && state == IN_DQUOTE)
			state = NOT_IN_QUOTE;
		if (state != IN_QUOTE)
		{
			env_value = find_env_value(str, *env_list);
			if (env_value != NULL)
			{
				replaced_str = replace_1st_env_var(str_head, env_value);
				free(str_head);
				str_head = replaced_str;
				state = NOT_IN_QUOTE;
				is_replaced_str = 1;
			}
		}
		if (is_replaced_str == 1)
		{
			str = replaced_str;
			is_replaced_str = 0;
		}
		else
			str++;
	}
	return (str_head);
}

t_token	*expand_env(t_token *tokens, t_dlist **env_list)
{
	t_token	*current;
	t_token	*expanded_tokens;
	t_token	*new_tokens_head;

	current = tokens;
	while (current != NULL)
	{
		if (current->prev != NULL && current->prev->type == D_LESSER)
		{ // heredocのdelimiterは変数展開しない
			current = current->next;
			continue ;
		}
		// 環境変数の置換
		current->str = replace_env_var(current->str, env_list);
		// 置換後の文字列が引用符で囲まれていない場合、空白区切りでトークン化
		expanded_tokens = tokenize(current->str);		
		// トークン化した文字列を元のトークンリストの間に挿入
		insert_between_tokens(expanded_tokens, current, &new_tokens_head);
		// 引用符を削除する
		current = trim_quotes(expanded_tokens);
		current = current->next;
	}
	ft_debug("--- after expand_env ---\n");
	print_tokens(new_tokens_head);
	return (new_tokens_head);
}
