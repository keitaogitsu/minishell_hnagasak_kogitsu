/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:44:53 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/20 04:39:13 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

static int	is_invalid_key(char *key)
{
	if (ft_isdigit(key[0]) || key[0] == '=')
		return (1);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (1);
		key++;
	}
	return (0);
}

static int	print_unset_err(char *key)
{
	ft_errmsg("minishell: unset: ");
	ft_errmsg(key);
	ft_errmsg(" : not a valid identifier\n");
	return (EXIT_FAILURE);
}

int	ft_unset(char *argv[], t_dlist **env_list)
{
	int	argc;
	int	i;
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	argc = get_argc(argv);
	if (argc < 2)
		return (exit_status);
	i = 1;
	while (i < argc)
	{
		if (is_invalid_key(argv[i]))
			exit_status = print_unset_err(argv[i]);
		else
			remove_env(argv[i], env_list);
		i++;
	}
	return (exit_status);
}
