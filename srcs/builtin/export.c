/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:34:31 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/20 04:26:49 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "free.h"
#include "util.h"

static int	is_invalid_key_value(char *key_value)
{
	char	*key;
	char	*value;
	int		i;

	if (ft_isdigit(key_value[0]) || key_value[0] == '=')
		return (1);
	get_key_value(key_value, &key, &value);
	if (key == NULL)
		key = ft_strdup(key_value);
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

static void	export_env_value(t_dlist **env_list, char *key_value)
{
	char	*key;
	char	*value;

	get_key_value(key_value, &key, &value);
	if (key == NULL)
		return ;
	if (!find_existing_env(key, env_list))
		ft_dlstadd_back(env_list, ft_dlstnew(to_env(key_value, !IS_SHELL_VAR)));
	else
		update_env_value(env_list, key_value);
	ft_free(key);
	ft_free(value);
}

static int	print_export_err(char *key_value)
{
	ft_errmsg("minishell: export: ");
	ft_errmsg(key_value);
	ft_errmsg(" : not a valid identifier\n");
	return (EXIT_FAILURE);
}

static int	print_declare_env(t_dlist *env_list)
{
	t_env	*env;
	t_dlist	*current;

	current = env_list;
	while (current)
	{
		env = (t_env *)current->cont;
		if (!env->is_shell_var)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		current = current->nxt;
	}
	return (EXIT_SUCCESS);
}

int	ft_export(char *argv[], t_dlist **env_list)
{
	char	*key_value;
	int		argc;
	int		i;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	argc = get_argc(argv);
	if (argc == 1)
		return (print_declare_env(*env_list));
	i = 1;
	while (i < argc)
	{
		key_value = argv[i];
		if (is_invalid_key_value(key_value))
			exit_status = print_export_err(key_value);
		else
			export_env_value(env_list, key_value);
		i++;
	}
	return (exit_status);
}
