/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:34:31 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/17 19:49:51 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "free.h"
#include "util.h"

static int	is_invalid_arg(char **argv)
{
	char	*key;
	char	*value;
	int		i;

	if (ft_isdigit(argv[1][0]) || argv[1][0] == '=')
	{
		// ft_errmsg("minishell: export: not a valid identifier\n");
		return (1);
	}
	get_key_value(argv[1], &key, &value);
	if (key == NULL)
		key = ft_strdup(argv[1]);
	i = 0;
	while (key[i])
	{
		// printf("is_invalid_arg *key:%c\n", key[i]);
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			// ft_errmsg("minishell: export: not a valid identifier2\n");
			ft_free(key);
			ft_free(value);
			return (1);
		}
		i++;
	}
	ft_free(key);
	ft_free(value);
	return (0);
}

void	ft_export(char *argv[], t_dlist **env_list)
{
	char	*str_env;
	char	*key;
	char	*value;

	if (is_invalid_arg(argv))
	{
		ft_errmsg("minishell: export: not a valid identifier\n");
		return ;
	}
	str_env = argv[1];
	get_key_value(str_env, &key, &value);
	if (key == NULL)
		return ;
	if (!find_existing_env(key, env_list))
		ft_dlstadd_back(env_list, ft_dlstnew(to_env(str_env, !IS_SHELL_VAR)));
	else
		update_env_value(env_list, str_env);
	ft_free(key);
	ft_free(value);
}
