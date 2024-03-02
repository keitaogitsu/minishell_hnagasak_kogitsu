/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:18:48 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/01 15:03:35 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_env(char **argv, t_dlist **env_list)
{
	t_env	*env;
	t_dlist	*current;

	if (get_argc(argv) != 1)
	{
		ft_errmsg("Too many arguments\n");
		return ;
	}
	current = *env_list;
	while (current)
	{
		env = current->cont;
		printf("%s=%s\n", env->key, env->value);
		current = current->nxt;
	}
}
