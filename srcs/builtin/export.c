/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:34:31 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/25 18:09:27 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "util.h"

t_env	*find_existing_env(char *str_env, t_dlist **env_list)
{
	t_dlist	*current;
	t_env	*env;

	current = *env_list;
	while (current)
	{
		env = (t_env *)current->cont;
		if (ft_strncmp(env->key, str_env, ft_strlen(str_env)) == 0)
			return (env);
		current = current->nxt;
	}
	return (NULL);
}

void	ft_export(char *argv[], t_dlist **env_list)
{
	char	*str_env;
	t_env	*env;

	str_env = argv[1];
	if (!find_existing_env(str_env, env_list))
	{
		env = to_env(str_env, !IS_SHELL_VAR);
		ft_dlstadd_back(env_list, ft_dlstnew(env));
	}
	else
		update_env_value(env_list, str_env);
}
