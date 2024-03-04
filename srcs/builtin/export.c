/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:34:31 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/04 19:06:14 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "util.h"

static int	is_invalid_arg(char **argv)
{
	char	*key;
	char	*value;

	if (ft_isdigit(argv[1][0]) || argv[1][0] == '=')
	{
		ft_errmsg("minishell: export: not a valid identifier\n");
		return (1);
	}
	get_key_value(argv[1], &key, &value);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
		{
			ft_errmsg("minishell: export: not a valid identifier2\n");
			return (1);
		}
		key++;
	}
	return (0);
}

void	ft_export(char *argv[], t_dlist **env_list)
{
	char	*str_env;
	t_env	*env;

	is_invalid_arg(argv);
	str_env = argv[1];
	if (!find_existing_env(str_env, env_list))
	{
		env = to_env(str_env, !IS_SHELL_VAR);
		ft_dlstadd_back(env_list, ft_dlstnew(env));
	}
	else
		update_env_value(env_list, str_env);
}
