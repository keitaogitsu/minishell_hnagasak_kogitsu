/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:18:48 by hnagasak          #+#    #+#             */
/*   Updated: 2023/12/29 19:43:16 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// void	ft_env(char *argv[])
// {
// 	int i;

// 	i = 0;
// 	while (argv[i])
// 	{
// 		printf("%s\n", argv[i]);
// 		i++;
// 	}
// }

void ft_env(t_dlist **env_list)
{
	t_env	*env;
	t_dlist	*current;

	current = *env_list;
	while (current)
	{
		// printf("## current:%p, %p\n", current, current->cont);
		env = current->cont;
		printf("%s=%s\n", env->key,env->value);
		// printf("is_shell_var: %d\n", env->is_shell_var);
		current = current->nxt;
	}
}