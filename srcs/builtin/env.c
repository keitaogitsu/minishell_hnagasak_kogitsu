/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:18:48 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/03 15:38:25 by kogitsu          ###   ########.fr       */
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

void	ft_env(char **argv, t_dlist **env_list)
{
	t_env *env;
	t_dlist *current;

	if (get_argc(argv) != 1)
	{
		printf("Too many arguments\n");
		return ;
	}

	current = *env_list;
	while (current)
	{
		// printf("## current:%p, %p\n", current, current->cont);
		env = current->cont;
		printf("[%s=%s]\n", env->key, env->value);
		// printf("is_shell_var: %d\n", env->is_shell_var);
		current = current->nxt;
	}
}