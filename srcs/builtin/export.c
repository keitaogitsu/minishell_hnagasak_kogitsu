/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:34:31 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/17 21:42:32 by hnagasak         ###   ########.fr       */
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
		return (1);
	get_key_value(argv[1], &key, &value);
	if (key == NULL)
		key = ft_strdup(argv[1]);
	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
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

int	ft_export(char *argv[], t_dlist **env_list)
{
	char	*str_env;
	char	*key;
	char	*value;

	if (is_invalid_arg(argv))
	{
		ft_errmsg("minishell: export: not a valid identifier\n");
		return (EXIT_FAILURE);
	}
	str_env = argv[1];
	get_key_value(str_env, &key, &value);
	if (key == NULL)
		return (EXIT_SUCCESS);
	if (!find_existing_env(key, env_list))
		ft_dlstadd_back(env_list, ft_dlstnew(to_env(str_env, !IS_SHELL_VAR)));
	else
		update_env_value(env_list, str_env);
	ft_free(key);
	ft_free(value);
	return (EXIT_SUCCESS);
}
