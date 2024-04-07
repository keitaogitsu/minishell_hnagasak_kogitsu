/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:52:02 by hnagasak          #+#    #+#             */
/*   Updated: 2024/04/07 15:30:37 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static size_t	get_keystrlen(char *str)
{
	size_t	len;

	len = 0;
	while (is_env_key_char(str[len]))
		len++;
	return (len);
}

/**
 * @brief Retrieves the value of an environment variable from a list.
 * @param char_position Pointer to the start of the variable name.
 * @param env_list Pointer to the list of environment variables.
 * @return The variable's value if found, else an empty string.
 */
char	*find_env_value(char *char_position, t_dlist *env_list)
{
	t_env	*env;
	size_t	len;

	if (*char_position != '$')
		return (NULL);
	char_position++;
	len = get_keystrlen(char_position);
	if (len == 0)
		return (NULL);
	while (env_list != NULL)
	{
		env = (t_env *)env_list->cont;
		if (ft_strlen(env->key) == len && ft_strncmp(env->key, char_position,
				ft_strlen(env->key)) == 0)
			return (env->value);
		env_list = (env_list)->nxt;
	}
	return ("");
}

static size_t	toggle_quote_state(size_t state, char *str)
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

char	*replace_env_var(char *str, t_dlist **env_list, int exit_status)
{
	char	*env_value;
	size_t	state;
	char	*str_head;

	state = NOT_IN_QUOTE;
	str_head = str;
	while (*str != '\0')
	{
		state = toggle_quote_state(state, str);
		if (state != IN_QUOTE)
		{
			if (ft_strncmp(str, "$?", ft_strlen("$?")) == 0)
				replace_exit_status(&str_head, &str, exit_status);
			else
			{
				env_value = find_env_value(str, *env_list);
				if (env_value != NULL)
					replace_env_value(&str_head, &str, env_value);
			}
		}
		str++;
	}
	return (str_head);
}
