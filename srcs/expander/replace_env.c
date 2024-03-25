/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:52:02 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/22 10:34:36 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		while (is_env_key_char(*char_position))
			char_position++;
		if (start == char_position)
			return (NULL);
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
	while (str != *start)
	{
		*new_str = *str;
		new_str++;
		str++;
	}
	copy_str_func(&new_str, &env_value, '\0');
	str++;
	while (is_env_key_char(*str) || *str == '?')
		str++;
	*start = new_str - 1;
	copy_str_func(&new_str, &str, '\0');
	*new_str = '\0';
	free(*str_head);
	*str_head = new_str_head;
}

void	replace_exit_status(char **str_head, char **start, int exit_status)
{
	char	*new_str;
	char	*new_str_head;
	char	*str;
	char	*str_exit_status;

	str_exit_status = ft_itoa(exit_status);
	new_str = ft_malloc(sizeof(char) * (ft_strlen(*str_head)
				+ ft_strlen(str_exit_status) + 1));
	str = *str_head;
	new_str_head = new_str;
	while (str != *start)
	{
		*new_str = *str;
		new_str++;
		str++;
	}
	copy_str_func(&new_str, &str_exit_status, '\0');
	str++;
	while (*str == '?')
		str++;
	*start = new_str - 1;
	copy_str_func(&new_str, &str, '\0');
	*new_str = '\0';
	free(*str_head);
	*str_head = new_str_head;
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
