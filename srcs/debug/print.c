/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:27:01 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/28 21:05:18 by hnagasak         ###   ########.fr       */
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

// void	ft_debug(const char *format, ...)
// {
// 	va_list	args;

// 	if (DEBUG)
// 	{
// 		va_start(args, format);
// 		vfprintf(stderr, format, args);
// 		va_end(args);
// 	}
// }

void	ft_debug(const char *format, ...)
{
	(void)format;
}
