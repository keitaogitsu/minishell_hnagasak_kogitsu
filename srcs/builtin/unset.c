/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:44:53 by hnagasak          #+#    #+#             */
/*   Updated: 2023/12/29 19:55:33 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_unset(char *argv[], t_dlist **env_list)
{
	int i;
	t_dlist *current;
	t_env *env;

	printf("--- ft_unset ---\n");

	current = *env_list;
	while (current != NULL)
	{
		env = (t_env *)current->cont;
		if (ft_strncmp(env->key, argv[1], ft_strlen(env->key)) == 0)
		{
			printf("key: %s value: %s\n", env->key, env->value);

			if (current->prv != NULL)
				current->prv->nxt = current->nxt;
			if (current->nxt != NULL)
				current->nxt->prv = current->prv;
			free(env->key);
			free(env->value);
			free(env);
			free(current);
			return ;
		}
		// printf("key: %s value: %s\n", env->key, env->value);
		current = current->nxt;
	}
}