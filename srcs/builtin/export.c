/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:34:31 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/29 19:25:36 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "util.h"

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
