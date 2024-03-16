/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:27:21 by kogitsu           #+#    #+#             */
/*   Updated: 2024/03/16 17:22:09 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "expander.h"

int	is_env_key_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

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
		while (is_env_key_char(*char_position))
			char_position++;
		while (env_list != NULL)
		{
			env = (t_env *)env_list->cont;
			if (ft_strncmp(env->key, start, ft_strlen(env->key)) == 0
				&& !is_env_key_char(*char_position))
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
void	replace_env_value(char **str_head, char **start, char *env_value)
{
	char	*new_str;
	char	*new_str_head;
	char	*str;

	new_str = ft_malloc(sizeof(char) * (ft_strlen(*str_head)
				+ ft_strlen(env_value) + 1));
	str = *str_head;
	new_str_head = new_str;
	while (str != *start) // 展開する位置まではstrをコピー
	{
		*new_str = *str;
		new_str++;
		str++;
	}
	copy_str_func(&new_str, &env_value, '\0');
	// strを環境変数の終わりまで進める
	str++;
	while (is_env_key_char(*str))
		str++;
	*start = new_str - 1;
	copy_str_func(&new_str, &str, '\0'); // 環境変数以降をコピー
	*new_str = '\0';
	free(*str_head);
	*str_head = new_str_head;
}

void	insert_between_tokens(t_token *expanded_tokens, t_token *current,
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

void	trim_and_change_state(char **str, char **quote_removed_str,
		size_t *state)
{
	if (**str == '\\' && *(*str + 1) == '\'' && *state == NOT_IN_QUOTE)
	{
		(*str)++;
		**quote_removed_str = **str;
		(*quote_removed_str)++;
	}
	else if (**str == '\\' && *(*str + 1) == '\"' && *state == NOT_IN_QUOTE)
	{
		(*str)++;
		**quote_removed_str = **str;
		(*quote_removed_str)++;
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

size_t	toggle_quote_state(size_t state, char *str)
{
	if (*str == '\'' && state == NOT_IN_QUOTE)
		return (IN_QUOTE);
	else if (*str == '\'' && state == IN_QUOTE)
		return (NOT_IN_QUOTE);
	else if (*str == '\"' && state == NOT_IN_QUOTE)
		return (IN_DQUOTE);
	else if (*str == '\"' && state == IN_DQUOTE)
		return (NOT_IN_QUOTE);
	return (state);
}

// void	replace_env_vars_in_str(char *str, char *replaced_str,
// t_dlist **env_list)
// {
// 	char *env_value;

// 	env_value = find_env_value(str, *env_list);
// 	if (env_value != NULL)
// 	{
// 		replaced_str = replace_1st_env_var(str_head, env_value);
// 		free(str_head);
// 		str_head = replaced_str;
// 		state = NOT_IN_QUOTE;
// 		is_replaced_str = 1;
// 	}
// }

// char *replace_with_env_value(char *str, char *str_head, t_dlist **env_list,
// int *is_replaced_str)
// {
// 	char *env_value;
// 	char *replaced_str;

// 	env_value = find_env_value(str, *env_list);
// 	if (env_value != NULL)
// 	{
// 		replaced_str = replace_1st_env_var(str_head, env_value);
// 		free(str_head);
// 		str_head = replaced_str;
// 		*is_replaced_str = 1;
// 	}
// 	return (str_head);
// }

// char *handle_replaced_string(char *str, char *replaced_str,
// int *is_replaced_str, size_t *state)
// {
// 	if (*is_replaced_str == 1)
// 	{
// 		str = replaced_str;
// 		*is_replaced_str = 0;
// 		*state = NOT_IN_QUOTE;
// 	}
// 	else
// 		str++;
// 	return (str);
// }

// char	*replace_env_var(char *str, t_dlist **env_list)
// {
//     char	*replaced_str;
//     size_t	state;
//     char	*str_head;
//     int		is_replaced_str;

//     is_replaced_str = 0;
//     state = NOT_IN_QUOTE;
//     str_head = str;
//     while (*str != '\0')
//     {
//         state = toggle_quote_state(state, str);
//         if (state != IN_QUOTE)
//         {
//             replaced_str = replace_with_env_value(str, str_head, env_list,
// &is_replaced_str);
//             str_head = replaced_str;
//         }
//         str = handle_replaced_string(str, replaced_str, &is_replaced_str,
// &state);
//     }
//     return (str_head);
// }

char	*replace_env_var(char *str, t_dlist **env_list)
{
	char	*env_value;
	size_t	state;
	char	*str_head;

	state = NOT_IN_QUOTE;
	str_head = str;
	// int i = 0;
	while (*str != '\0')
	{
		state = toggle_quote_state(state, str);
		if (state != IN_QUOTE)
		{
			// 現在位置の文字列が環境変数かどうかを判定
			env_value = find_env_value(str, *env_list);
			if (env_value != NULL)
				replace_env_value(&str_head, &str, env_value);
		}
		str++;
	}
	return (str_head);
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

t_token	*expand_env(t_token *tokens, t_dlist **env_list)
{
	t_token	*current;
	t_token	*expanded_tokens;
	t_token	*new_tokens_head;

	current = tokens;
	while (current != NULL)
	{
		if (current->prev != NULL && current->prev->type == D_LESSER)
		{
			current = current->next;
			continue ;
		}
		current->str = replace_env_var(current->str, env_list);
		expanded_tokens = tokenize(current->str);
		handle_expanded_tokens(&expanded_tokens, &current, &new_tokens_head);
		current = current->next;
	}
	return (new_tokens_head);
}
// ft_debug("--- after expand_env ---\n");
// print_tokens(new_tokens_head);
