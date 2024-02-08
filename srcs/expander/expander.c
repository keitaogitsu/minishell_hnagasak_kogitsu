/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:27:21 by kogitsu           #+#    #+#             */
/*   Updated: 2024/02/03 18:29:35 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char    *find_env(char *char_position, t_dlist *env_list)
{
    char *start;
    size_t key_len;
    
    if (*char_position == '$')
    {
        char_position++;
        start = char_position;
        while (*char_position != '\"' && *char_position != '\'' && *char_position != ' ' && *char_position != '$' && *char_position != '\0')
            char_position++;
        key_len = char_position - start;
        while (env_list != NULL)
        {
            printf("key:%s, start:%s len:%zu\n",((t_env *)env_list->cont)->key, start, key_len);
            if (ft_strncmp(((t_env *)env_list->cont)->key, start, key_len) == 0)
                return (((t_env *)(env_list)->cont)->value);
            env_list = (env_list)->nxt;
        }
        return ("");
    }
    return (NULL);
}

char    *expand_env_var(char *str, char *env_value)
{
    size_t value_len;
    size_t str_len;
    char *new_str;
    char *new_str_head;

    value_len = ft_strlen(env_value);
    str_len = ft_strlen(str);
    new_str = (char *)malloc(sizeof(char) * (str_len + value_len + 1));
    if (new_str == NULL)
        return (NULL);
    new_str_head = new_str;
    // $直前まで元の文字列をコピー
    while (*str != '$')
    {
        *new_str = *str;
        new_str++;
        str++;
    }
    // 元の文字列を環境変数の次まで進める
    str++; // $をスキップ
    while (*str != '\"' && *str != '\'' && *str != ' ' && *str != '$' && *str != '\0')
        str++;
    // 環境変数部分のコピー
    while (*env_value != '\0')
    {
        *new_str = *env_value;
        new_str++;
        env_value++;
    }
    // 元の文字列の残りをコピー
    while (*str != '\0')
    {
        *new_str = *str;
        new_str++;
        str++;
    }
    *new_str = '\0';
    return (new_str_head);
}

void    insert_between_tokens(t_token *tokens, t_token *expanded_tokens, t_token *current)
{
    t_token	*token_next_expand;
	t_token *token_prev_expand;
	
	token_next_expand = current->next;
	token_prev_expand = tokens;
	if (current == tokens)
	{
		while (expanded_tokens->next != NULL)
			expanded_tokens = expanded_tokens->next;
		expanded_tokens->next = current->next;
	}
	else
	{
		while (token_prev_expand->next != current)
			token_prev_expand = token_prev_expand->next;
		token_prev_expand->next = expanded_tokens;
		while (expanded_tokens->next != NULL)
			expanded_tokens = expanded_tokens->next;
		expanded_tokens->next = token_next_expand;
	}
}

#include "debug.h"

t_token *expand_env(t_token *tokens, t_dlist **env_list)
{
    t_token *current;
    char *str_current;
    char *new_str;
    char *env_value;
    size_t state;
    int expand_flg;
    char *new_expanded_str_head;
    t_token *expanded_tokens;
    t_token *token_next_expand;

    expand_flg = 0;
    state = NOT_IN_QUOTE;
    current = tokens;
    while (current != NULL)
    {
        str_current = current->str;
        while (*str_current != '\0')
        {
            if (*str_current == '\'' && state == NOT_IN_QUOTE)
                state = IN_QUOTE;  
            else if (*str_current == '\'' && state == IN_QUOTE)
                state = NOT_IN_QUOTE;
            else if (*str_current == '\"' && state == NOT_IN_QUOTE)
                state = IN_DQUOTE;
            else if (*str_current == '\"' && state == IN_DQUOTE)
                state = NOT_IN_QUOTE;
            if(state != IN_QUOTE)
            {
                printf("1.  str:%c state:%zu\n", *str_current, state);
                env_value = find_env(str_current, *env_list);
                printf("2.  str:%c state:%zu\n", *str_current, state);
                if (env_value != NULL)
                {
                    printf("env_value: %s\n", env_value);
                    new_str = expand_env_var(current->str, env_value);
                    printf("new_str: %s\n", new_str);
                    free(current->str);
                    current->str = new_str;
                    str_current = new_str; // TODO: str_currentを＄の前まで進める
                    state = NOT_IN_QUOTE;
                    expand_flg = 1;
                }
            }
            if (expand_flg == 1)
                expand_flg = 0;
            else
                str_current++;
        }
		printf("3. current->str:%s\n", current->str);
		expanded_tokens = tokenize(current->str);
		print_tokens(expanded_tokens); 
		insert_between_tokens(tokens, expanded_tokens, current);
		printf("4. current->str:%s\n", current->str);
		current = expanded_tokens;
        // DQUOTEとQUOTEを消すecho
        str_current = current->str;
        state = NOT_IN_QUOTE;
        new_str = (char *)malloc(sizeof(char) * (ft_strlen(current->str) + 1));
        new_expanded_str_head = new_str;
        while (*str_current != '\0')
        {
            if (*str_current == '\\' && *(str_current + 1) == '\'' && state == NOT_IN_QUOTE)
            {
                str_current++;
                *new_str = *str_current;
                new_str++;
            }
            else if (*str_current == '\\' && *(str_current + 1)== '\"' && state == NOT_IN_QUOTE)
            {
                str_current++;
                *new_str = *str_current;
                new_str++;
            }
            else if (*str_current == '\'' && state == NOT_IN_QUOTE)
                state = IN_QUOTE;  
            else if (*str_current == '\'' && state == IN_QUOTE)
                state = NOT_IN_QUOTE;
            else if (*str_current == '\"' && state == NOT_IN_QUOTE)
                state = IN_DQUOTE;
            else if (*str_current == '\"' && state == IN_DQUOTE)
                state = NOT_IN_QUOTE;
            else
            {
                *new_str = *str_current;
                new_str++;
            }
            printf("str:%c state:%zu\n", *str_current, state);
            str_current++;
        }
        *new_str = '\0';
        current->str = new_expanded_str_head;
		printf("new_expanded_str_head:%s\n", new_expanded_str_head);
        // expanded_tokens = tokenize(current->str);
		// printf("1. current->str:%s\n", current->str);
		// print_tokens(expanded_tokens); 
		// insert_between_tokens(tokens, expanded_tokens, current);
        current = current->next;
    }
    return (tokens);
}