/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:52:02 by hnagasak          #+#    #+#             */
/*   Updated: 2024/04/05 06:23:50 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	strcpy2end(char **dst, char **src, char end)
{
	size_t	i;

	i = 0;
	while ((*src)[i] != end)
	{
		**dst = (*src)[i];
		i++;
		(*dst)++;
	}
}

static void	strcpy2ptr(char **dst, char **src, char *ptr)
{
	while (*src != ptr)
	{
		**dst = **src;
		(*dst)++;
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
	strcpy2end(&new_str, &env_value, '\0');
	str++;
	while (is_env_key_char(*str) || *str == '?')
		str++;
	*start = new_str - 1;
	strcpy2end(&new_str, &str, '\0');
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
	strcpy2ptr(&new_str, &str, *start);
	strcpy2end(&new_str, &str_exit_status, '\0');
	str++;
	while (*str == '?')
		str++;
	*start = new_str - 1;
	strcpy2end(&new_str, &str, '\0');
	*new_str = '\0';
	free(*str_head);
	free(str_exit_status);
	*str_head = new_str_head;
}
