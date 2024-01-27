/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:27:21 by kogitsu           #+#    #+#             */
/*   Updated: 2024/01/27 17:48:52 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// char   *get_env_value(char *env_name, t_dlist **env_list)
// {
//     t_dlist	*current;
//     char	*env_value;

//     current = *env_list;
//     while (current != NULL)
//     {
//         if (ft_strcmp(((t_env *)current->cont)->key, env_name) == 0)
//         {
//             env_value = ((t_env *)current->cont)->value;
//             return (env_value);
//         }
//         current = current->nxt;
//     }
//     return (NULL);
// }

// t_token    *expand_env_var(t_token *current, t_dlist **env_list)
// {
//     t_token	*new;
//     t_token	*next;
//     char	*env_value;

//     env_value = get_env_value(current->str + 1, env_list);
//     if (env_value == NULL)
//         new = token_init(0);
//     else
//         new = token_init(ft_strlen(env_value));
//     ft_strcpy(new->str, env_value);
//     next = current->next;
//     free(current);
//     return (new);
// }

char    *find_env(char *char_position, t_dlist **env_list)
{
    char *start;
    size_t env_len;
    
    if (*char_position == '$')
    {
        char_position++;
        start = char_position;
        while (*char_position != '\0' && *char_position != ' ' && *char_position != '$')
            char_position++;
        env_len = char_position - start;
        while (*env_list != NULL)
        {
            if (ft_strncmp(((t_env *)(*env_list)->cont)->key, start, env_len) == 0)
                return (((t_env *)(*env_list)->cont)->value);
            *env_list = (*env_list)->nxt;
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
    while (*str != '$')
    {
        *new_str = *str;
        new_str++;
        str++;
    }
    while (*str != '\0' && *str != ' ' && *str != '$')
        str++;
    while (*env_value != '\0')
    {
        *new_str = *env_value;
        new_str++;
        env_value++;
    }
    while (*str != '\0')
    {
        *new_str = *str;
        new_str++;
        str++;
    }
    return (new_str_head);
}

t_token *expand_env(t_token *tokens, t_dlist **env_list)
{
    t_token *current;
    char *str_current;
    char *new_str;
    char *env_value;

    current = tokens;
    while (current != NULL)
    {
        if (current->type == CHAR_DQUOTE)
        {
            str_current = current->str + 1;
            printf("42tokyo %s : %s\n", current->str, str_current);
            while (*str_current != CHAR_DQUOTE)
            {
                env_value = find_env(str_current, env_list);
                if (env_value != NULL)
                {
                    printf("env_value: %s\n", env_value);
                    new_str = expand_env_var(current->str, env_value);
                    printf("new_str: %s\n", new_str);
                    free(current->str);
                    current->str = new_str;
                    str_current = new_str;
                }
                str_current++;
            }
        }
        current = current->next;
    }
    return (tokens);
}