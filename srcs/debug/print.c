/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:27:01 by hnagasak          #+#    #+#             */
/*   Updated: 2024/01/04 17:31:06 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_env(t_dlist *env_list)
{
	t_env *env;
	t_dlist *current;

	current = env_list;
	printf("--- print_env ----\n");
	while (current)
	{
		// printf("## current:%p, %p\n", current, current->cont);
		env = current->cont;
		printf("%s=%s , is_shell_var = %d\n", env->key, env->value,
			env->is_shell_var);
		// printf("is_shell_var: %d\n", env->is_shell_var);
		current = current->nxt;
	}
	printf("--- end print_env ----\n");
}