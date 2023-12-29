/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:34:31 by hnagasak          #+#    #+#             */
/*   Updated: 2023/12/29 19:44:01 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_export(char *argv[], t_dlist **env_list)
{
	char *str_env;
	t_env *env;
	t_dlist *new;

	str_env = argv[1];
	env = to_env(str_env, !IS_SHELL_VAR);
	ft_dlstadd_back(env_list, ft_dlstnew(env));
}
